-- Inner Join: Ученики и их классы
SELECT s.first_name, s.last_name, c.grade_level, c.letter
FROM students s
INNER JOIN classes c ON s.class_id = c.class_id; -- INNER JOIN оставляет только учеников с найденным классом; ON задает условие совпадения ID.

-- Left Join: Все учителя и их классное руководство (даже если у учителя нет класса)
SELECT t.first_name, t.last_name, c.grade_level, c.letter
FROM teachers t
LEFT JOIN classes c ON t.teacher_id = c.teacher_id; -- LEFT JOIN сохраняет всех учителей; если класса нет, данные класса будут NULL.

-- Right Join: Все классы и их классные руководители
SELECT c.grade_level, c.letter, t.first_name, t.last_name
FROM teachers t
RIGHT JOIN classes c ON t.teacher_id = c.teacher_id; -- RIGHT JOIN сохраняет все классы; если руководитель не найден, данные учителя будут NULL.

-- Full Join: Полный охват учителей и предметов
SELECT t.first_name, t.last_name, s.subject_name
FROM teachers t
FULL JOIN subjects s ON t.teacher_id = s.teacher_id; -- FULL JOIN показывает все строки обеих таблиц, соединяя совпавшие; для несовпавших данные другой таблицы будут NULL.