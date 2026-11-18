-- View 1: Полная информация об успеваемости учеников
CREATE VIEW v_student_grades AS -- Создает представление — сохраненный запрос с именем v_student_grades.
SELECT 
    s.first_name || ' ' || s.last_name AS student_full_name, -- || объединяет имя, пробел и фамилию в полное имя.
    sub.subject_name,
    g.grade,
    g.grade_date
FROM grades g
JOIN students s ON g.student_id = s.student_id -- JOIN добавляет данные ученика, у которого совпадает ID.
JOIN subjects sub ON g.subject_id = sub.subject_id; -- JOIN добавляет предмет, у которого совпадает ID.

-- View 2: Расписание занятий с читаемыми названиями классов, предметов и кабинетов
CREATE VIEW v_full_schedule AS -- Создает представление с именем v_full_schedule.
SELECT 
    sch.day_of_week,
    sch.lesson_number,
    c.grade_level || c.letter AS class_name, -- || объединяет уровень класса и его букву в одно название.
    sub.subject_name,
    cl.room_number
FROM schedules sch
JOIN classes c ON sch.class_id = c.class_id -- Добавляет данные класса с совпадающим ID.
JOIN subjects sub ON sch.subject_id = sub.subject_id -- Добавляет предмет с совпадающим ID.
JOIN classrooms cl ON sch.classroom_id = cl.classroom_id; -- Добавляет кабинет с совпадающим ID.