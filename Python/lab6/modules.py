from datetime import datetime
from typing import Dict, Optional
from pydantic import BaseModel, Field


# Модель для создания новой задачи
class TaskCreate(BaseModel):
    title: str = Field(..., min_length=1, max_length=100)
    description: Optional[str] = None
    priority: str = Field(default="medium", pattern="^(low|medium|high)$")
    completed: bool = False
    deadline: Optional[datetime] = None


# Модель для полного обновления задачи (PUT)
class TaskUpdatePut(BaseModel):
    title: str = Field(..., min_length=1, max_length=100)
    description: Optional[str] = None
    priority: str = Field(..., pattern="^(low|medium|high)$")
    completed: bool
    deadline: Optional[datetime] = None


# Модель для частичного обновления задачи (PATCH)
class TaskUpdatePatch(BaseModel):
    title: Optional[str] = Field(None, min_length=1, max_length=100)
    description: Optional[str] = None
    priority: Optional[str] = Field(None, pattern="^(low|medium|high)$")
    deadline: Optional[datetime] = None


# Модель, которую API возвращает пользователю
class TaskResponse(BaseModel):
    id: int
    title: str
    description: Optional[str] = None
    priority: str
    completed: bool
    deadline: Optional[datetime] = None
    created_at: datetime
    completed_at: Optional[datetime] = None


# Модель для статистики
class TaskStatsResponse(BaseModel):
    total: int
    completed: int
    uncompleted: int
    overdue: int
    priority_distribution: Dict[str, int]