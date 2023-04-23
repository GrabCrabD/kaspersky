import uuid

from fastapi.testclient import TestClient

from search.main import app, search_files_by_text


def test_search_files_by_text():
    paths = [
        'tests/data/file1.c',
        'tests/data/file2.txt',
        'tests/data/file3.html',
        'tests/data/file4.HEIC',
        'tests/data/ernest hemingway.pdf',
    ]

    assert search_files_by_text(paths, "TEST") == [
        'tests/data/file1.c',
        'tests/data/file2.txt',
    ]


client = TestClient(app)


def test_create_task():
    response = client.post('/search', json={
        "text": "END_TEST",
        "file_mask": None,
        "size": None,
        "creation_time": None
    })

    assert response.status_code == 200

    data = response.json()
    assert "search_id" in data
    assert uuid.UUID(data["search_id"])
