-- UNION: Все фамилии учителей и учеников в одном списке
SELECT last_name FROM teachers
UNION -- Объединяет результаты и убирает повторяющиеся фамилии.
SELECT last_name FROM students;

-- INTERSECT: Пример пересечения (например, имена, которые есть и у учителей, и у учеников)
SELECT first_name FROM teachers
INTERSECT -- Оставляет только имена, присутствующие в обоих результатах.
SELECT first_name FROM students;

-- EXCEPT: Имена учителей, которых нет среди имен учеников
SELECT first_name FROM teachers
EXCEPT -- Оставляет имена из первого результата, которых нет во втором.
SELECT first_name FROM students;