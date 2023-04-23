import os
from dataclasses import dataclass, asdict
import json

main_path = '/Users/dmitriy/Downloads'
key_for_search = 'END_TEST'


@dataclass(frozen=True)
class result:
    finished: bool
    paths: str


answer_list = []


def search_files(main_path):
    for i in os.listdir(main_path):
        if os.path.isfile(main_path+'/'+i):
            try:
                with open(main_path+'/'+i) as r:
                    for j in r:
                        if key_for_search in j:
                            r = result(True, main_path+'/'+i)
                            answer_list.append(asdict(r))
                            break
            except:
                print('cannot open for search')

        if os.path.isdir(main_path+'/'+i):
            search_files(main_path+'/'+i)


search_files(main_path)
print(answer_list)

# def search(directory: Path, text: str, filters: dict):
#     for p in ...:
#         if p is ...:
#             with p.open():
