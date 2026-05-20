from datetime import datetime
from typing import List, Optional
from fastapi import FastAPI, HTTPException, Query
from modules import (
    TaskCreate,
    TaskResponse,
    TaskStatsResponse,
    TaskUpdatePatch,
    TaskUpdatePut,
)
from storage import storage

app = FastAPI(title="Advanced Task API", version="2.0")


# ==========================================
# ЧАСТЬ 1: БАЗОВЫЕ ЭНДПОИНТЫ
# ==========================================


@app.get("/")
def read_root():
    return {"message": "Advanced Task API", "version": "2.0"}


@app.get("/tasks", response_model=List[TaskResponse])
def get_tasks(
    completed: Optional[bool] = None,
    priority: Optional[str] = Query(None, pattern="^(low|medium|high)$"),
    limit: Optional[int] = None,
    sort_by: Optional[str] = Query(None, pattern="^(created_at|priority)$"),
):
    return storage.get_all(
        completed=completed, priority=priority, limit=limit, sort_by=sort_by
    )


@app.get("/tasks/search", response_model=List[TaskResponse])
def search_tasks(
    keyword: Optional[str] = None,
    priority: Optional[str] = Query(None, pattern="^(low|medium|high)$"),
    date_from: Optional[datetime] = None,
    date_to: Optional[datetime] = None,
):
    return storage.search(
        keyword=keyword,
        priority=priority,
        date_from=date_from,
        date_to=date_to,
    )


@app.get("/tasks/stats", response_model=TaskStatsResponse)
def get_tasks_stats():
    return storage.get_stats()


@app.get("/tasks/{task_id}", response_model=TaskResponse)
def get_task_by_id(task_id: int):
    task = storage.get_by_id(task_id)
    if not task:
        raise HTTPException(
            status_code=404, detail=f"Задача с ID {task_id} не найдена"
        )
    return task


@app.post("/tasks", response_model=TaskResponse, status_code=201)
def create_task(task: TaskCreate):
    if storage.is_title_exists(task.title):
        raise HTTPException(
            status_code=400,
            detail=f"Задача с названием '{task.title}' уже существует",
        )
    return storage.create(task.model_dump())


# ==========================================
# ЧАСТЬ 2: РАСШИРЕННЫЕ ОПЕРАЦИИ
# ==========================================


@app.put("/tasks/{task_id}", response_model=TaskResponse)
def update_task_put(task_id: int, task_data: TaskUpdatePut):
    if storage.is_title_exists(task_data.title, exclude_id=task_id):
        raise HTTPException(
            status_code=400,
            detail=f"Задача с названием '{task_data.title}' уже существует",
        )

    updated_task = storage.update(task_id, task_data.model_dump())
    if not updated_task:
        raise HTTPException(
            status_code=404, detail=f"Задача с ID {task_id} не найдена"
        )
    return updated_task


@app.patch("/tasks/{task_id}", response_model=TaskResponse)
def update_task_patch(task_id: int, task_data: TaskUpdatePatch):
    # Фильтруем только переданные пользователем поля (исключаем None)
    data_to_update = task_data.model_dump(exclude_unset=True)

    if "title" in data_to_update:
        if storage.is_title_exists(data_to_update["title"], exclude_id=task_id):
            raise HTTPException(
                status_code=400,
                detail=f"Задача с названием '{data_to_update['title']}' уже существует",
            )

    updated_task = storage.update(task_id, data_to_update)
    if not updated_task:
        raise HTTPException(
            status_code=404, detail=f"Задача с ID {task_id} не найдена"
        )
    return updated_task


@app.patch("/tasks/{task_id}/complete", response_model=TaskResponse)
def complete_task(task_id: int):
    task = storage.get_by_id(task_id)
    if not task:
        raise HTTPException(
            status_code=404, detail=f"Задача с ID {task_id} не найдена"
        )

    if task["completed"]:
        raise HTTPException(
            status_code=400, detail="Эта задача уже была выполнена"
        )

    updated_fields = {"completed": True, "completed_at": datetime.now()}
    return storage.update(task_id, updated_fields)


@app.delete("/tasks/{task_id}")
def delete_task(task_id: int):
    success = storage.delete(task_id)
    if not success:
        raise HTTPException(
            status_code=404, detail=f"Задача с ID {task_id} не найдена"
        )
    return {"message": f"Задача с ID {task_id} успешно удалена"}