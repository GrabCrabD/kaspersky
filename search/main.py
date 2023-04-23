import os
import fnmatch
from fastapi import FastAPI
from pydantic import BaseModel
from pydantic import BaseSettings
from concurrent.futures import ProcessPoolExecutor, as_completed
from typing import Optional
import uuid
import operator
import dateutil.parser
import dateutil.tz
import datetime


tasks = {}


class Settings(BaseSettings):
    main_path: str


settings = Settings()
app = FastAPI()
executor = ProcessPoolExecutor(max_workers=2)


# Schemas
class SizeParameter(BaseModel):
    value: int
    operator: str


class TimeParameter(BaseModel):
    value: str
    operator: str


class InputSearchParameters(BaseModel):
    text: Optional[str] = None
    file_mask: Optional[str] = None
    size: Optional[SizeParameter] = None
    creation_time: Optional[TimeParameter] = None


class OutputSearchResults(BaseModel):
    finished: bool
    paths: Optional[list[str]]


class OutputSearchID(BaseModel):
    search_id: uuid.UUID

# Core model


class SearchTask(BaseModel):
    id: uuid.UUID
    finished: bool
    parameters: InputSearchParameters
    paths: list[str]


@app.post('/search')
def create_task(parameters: InputSearchParameters) -> OutputSearchID:
    task = SearchTask(
        id=uuid.uuid4(),
        finished=False,
        parameters=parameters,
        paths=[]
    )
    submit_task(task)
    return OutputSearchID(search_id=task.id)


@app.get('/searches/{search_id}')
def get_task_results(search_id: uuid.UUID) -> OutputSearchResults:
    task: SearchTask = tasks[search_id]
    return OutputSearchResults(
        finished=task.finished,
        paths=task.paths,
    )


def get_all_files_recursive():
    all_files = []

    for root, _, files in os.walk(settings.main_path):
        for file in files:
            all_files.append(os.path.join(root, file))

    return all_files


def search_files_by_text(all_files: list[str], key_for_search: str):
    result = []

    for filepath in all_files:
        with open(filepath, 'rt', errors='ignore') as file:
            r = file.read()
            if r.find(key_for_search) != -1:
                result.append(filepath)

    return result


def search_files_by_file_mask(answer_list: list[str], file_mask: str):
    result = []

    for filepath in answer_list:
        if fnmatch.fnmatch(filepath, file_mask):
            result.append(filepath)

    return result


def search_file_by_size(answer_list: list[str], size_param: SizeParameter):
    result = []

    op = getattr(operator, size_param.operator)
    for filepath in answer_list:
        if op(size_param.value, os.stat(filepath).st_size):
            result.append(filepath)

    return result


def search_file_by_cr_time(answer_list: list[str], cr_time_param: TimeParameter):
    result = []

    op = getattr(operator, cr_time_param.operator)
    for filepath in answer_list:
        file_creation_time = datetime.datetime.fromtimestamp(
            os.stat('search.py').st_birthtime,
            dateutil.tz.tzutc(),
        )
        creation_time = dateutil.parser.parse(cr_time_param.value)
        if op(file_creation_time, creation_time):
            result.append(filepath)

    return result


def search_files(task: SearchTask) -> list[str]:
    result = get_all_files_recursive()

    if task.parameters.text:
        result = search_files_by_text(result, task.parameters.text)

    if task.parameters.file_mask:
        result = search_files_by_file_mask(result, task.parameters.file_mask)

    if task.parameters.size:
        result = search_file_by_size(result, task.parameters.size)

    if task.parameters.creation_time:
        result = search_file_by_cr_time(result, task.parameters.creation_time)

    return result


def submit_task(task):
    """Create a search task in a separate process"""
    def done_callback(future):
        task.finished = True
        task.paths = future.result()
        as_completed(future)

    tasks[task.id] = task
    future = executor.submit(search_files, task)
    future.add_done_callback(done_callback)
