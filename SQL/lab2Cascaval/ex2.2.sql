-- Subquery в WHERE: Ученики, у которых оценка выше среднего по всей школе
SELECT first_name, last_name
FROM students
WHERE student_id IN ( -- IN оставляет учеников, чей ID присутствует в результате подзапроса.
    SELECT student_id 
    FROM grades 
    WHERE grade > (SELECT AVG(grade) FROM grades) -- AVG вычисляет среднюю оценку; выбираются оценки выше этого среднего.
);

-- Subquery в FROM: Средний балл по предметам через подзапроса-таблицу
SELECT sub.subject_id, sub.avg_g
FROM ( -- Подзапрос формирует временную таблицу с результатами для основного запроса.
    SELECT subject_id, AVG(grade) AS avg_g -- AVG вычисляет среднюю оценку каждого предмета.
    FROM grades
    GROUP BY subject_id -- Объединяет оценки по предметам, чтобы AVG считала среднее отдельно для каждого.
) AS sub -- sub — короткое имя временной таблицы из подзапроса.
WHERE sub.avg_g > 7; -- Оставляет предметы со средним баллом выше 7.