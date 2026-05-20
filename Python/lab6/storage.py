from datetime import datetime
from typing import Any, Dict, List, Optional


class TaskStorage:

    def __init__(self):
        self.tasks: List[Dict[str, Any]] = []
        self.archived_tasks: List[Dict[str, Any]] = []
        self._current_id = 1

    def _archive_if_needed(self):
        """Если задач больше 20, самые старые перемещаются в архив"""
        if len(self.tasks) > 20:
            # Сортируем по дате создания, чтобы найти самые старые
            self.tasks.sort(key=lambda t: t["created_at"])
            # Определяем количество задач для переноса
            count_to_archive = len(self.tasks) - 20

            for _ in range(count_to_archive):
                old_task = self.tasks.pop(0)
                self.archived_tasks.append(old_task)

    def is_title_exists(
        self, title: str, exclude_id: Optional[int] = None
    ) -> bool:
        """Проверяет уникальность названия задачи"""
        for t in self.tasks:
            if t["title"].lower() == title.lower() and t["id"] != exclude_id:
                return True
        return False

    def create(self, task_data: Dict[str, Any]) -> Dict[str, Any]:
        """Создание новой задачи"""
        task_data["id"] = self._current_id
        task_data["created_at"] = datetime.now()
        task_data["completed_at"] = (
            datetime.now() if task_data.get("completed") else None
        )

        self._current_id += 1
        self.tasks.append(task_data)
        self._archive_if_needed()
        return task_data

    def get_by_id(self, task_id: int) -> Optional[Dict[str, Any]]:
        """Получение задачи по ID"""
        for t in self.tasks:
            if t["id"] == task_id:
                return t
        return None

    def get_all(
        self,
        completed: Optional[bool] = None,
        priority: Optional[str] = None,
        limit: Optional[int] = None,
        sort_by: Optional[str] = None,
    ) -> List[Dict[str, Any]]:
        """Получение списка задач с фильтрацией и сортировкой"""
        result = list(self.tasks)

        # Фильтрация
        if completed is not None:
            result = [t for t in result if t["completed"] == completed]
        if priority is not None:
            result = [t for t in result if t["priority"] == priority]

        # Сортировка
        if sort_by == "created_at":
            result.sort(key=lambda t: t["created_at"])
        elif sort_by == "priority":
            # Веса для приоритетов: high (0) -> medium (1) -> low (2)
            priority_weights = {"high": 0, "medium": 1, "low": 2}
            result.sort(key=lambda t: priority_weights.get(t["priority"], 99))

        # Ограничение количества
        if limit is not None and limit > 0:
            result = result[:limit]

        return result

    def update(self, task_id: int, updated_fields: Dict[str, Any]) -> Optional[Dict[str, Any]]:
        """Обновление полей задачи"""
        task = self.get_by_id(task_id)
        if not task:
            return None

        for key, value in updated_fields.items():
            task[key] = value

        # Корректировка completed_at при изменении статуса
        if "completed" in updated_fields:
            if updated_fields["completed"] and not task.get("completed_at"):
                task["completed_at"] = datetime.now()
            elif not updated_fields["completed"]:
                task["completed_at"] = None

        return task

    def delete(self, task_id: int) -> bool:
        """Удаление задачи"""
        task = self.get_by_id(task_id)
        if task:
            self.tasks.remove(task)
            return True
        return False

    def search(
        self,
        keyword: Optional[str] = None,
        priority: Optional[str] = None,
        date_from: Optional[datetime] = None,
        date_to: Optional[datetime] = None,
    ) -> List[Dict[str, Any]]:
        """Расширенный поиск задач"""
        result = list(self.tasks)

        if keyword:
            k = keyword.lower()
            result = [
                t
                for t in result
                if k in t["title"].lower()
                or (t["description"] and k in t["description"].lower())
            ]

        if priority:
            result = [t for t in result if t["priority"] == priority]

        if date_from:
            result = [t for t in result if t["created_at"] >= date_from]

        if date_to:
            result = [t for t in result if t["created_at"] <= date_to]

        return result

    def get_stats(self) -> Dict[str, Any]:
        """Расчет аналитической статистики"""
        now = datetime.now()
        total = len(self.tasks)
        completed = sum(1 for t in self.tasks if t["completed"])
        uncompleted = total - completed

        overdue = sum(
            1
            for t in self.tasks
            if not t["completed"]
            and t["deadline"] is not None
            and t["deadline"] < now
        )

        priority_dist = {"high": 0, "medium": 0, "low": 0}
        for t in self.tasks:
            p = t["priority"]
            if p in priority_dist:
                priority_dist[p] += 1

        return {
            "total": total,
            "completed": completed,
            "uncompleted": uncompleted,
            "overdue": overdue,
            "priority_distribution": priority_dist,
        }


# Инициализация единого объекта хранилища для приложения
storage = TaskStorage()