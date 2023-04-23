## Run server

```bash
MAIN_PATH=. uvicorn search.main:app --reload
```

## Run tests

```bash
MAIN_PATH=tests/data PYTHONPATH=. pytest
```

## Create search

```bash
curl --request POST --url http://127.0.0.1:8000/search --header "Content-Type: application/json" --data '{"text": "END_TEST", "file_mask": null, "size": null, "creation_time": null}'
```

## Get search

```bash
curl --request GET --url http://127.0.0.1:8000/searches/<id>
```