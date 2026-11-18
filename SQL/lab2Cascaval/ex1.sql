-- 1. Строковые функции (UPPER, CONCAT, SUBSTRING) + WHERE + ORDER BY
SELECT 
    UPPER(last_name) AS upper_last_name, -- UPPER переводит фамилию в верхний регистр.
    CONCAT(first_name, ' ', last_name) AS full_name, -- CONCAT объединяет имя, пробел и фамилию в одну строку.
    SUBSTRING(email, 1, 3) AS email_prefix -- SUBSTRING берет из email 3 символа, начиная с первого.
FROM teachers
WHERE teacher_id > 1 -- Оставляет только записи, где teacher_id больше 1.
ORDER BY last_name ASC; -- Сортирует фамилии по возрастанию.

-- 2. Функции дат (CURRENT_DATE, EXTRACT) + Арифметика (возраст учеников) + WHERE
SELECT 
    first_name, 
    last_name, 
    birth_date,
    EXTRACT(YEAR FROM AGE(CURRENT_DATE, birth_date)) AS age_years, -- CURRENT_DATE возвращает сегодняшнюю дату; AGE считает промежуток от даты рождения до сегодня; EXTRACT берет из него количество лет.
    EXTRACT(YEAR FROM birth_date) + 18 AS adult_year -- EXTRACT берет год рождения; прибавление 18 показывает год, когда исполнится 18.
FROM students
WHERE birth_date >= '2008-01-01' -- Оставляет учеников, родившихся 1 января 2008 года или позже.
ORDER BY birth_date DESC; -- Сортирует даты рождения от более поздней к более ранней.

-- 3. Арифметика (умножение вместимости кабинета на коэффициент) + WHERE
SELECT 
    room_number,
    max_seats,
    max_seats * 2 AS double_capacity_estimation -- Умножает вместимость на 2 и показывает результат под новым именем.
FROM classrooms
WHERE max_seats >= 25 -- Оставляет кабинеты вместимостью не менее 25 мест.
ORDER BY max_seats DESC; -- Сначала показывает кабинеты с наибольшей вместимостью.

-- 4. Работа с датами (форматирование/сравнение) + WHERE
SELECT 
    student_id, 
    grade, 
    grade_date,
    grade_date + INTERVAL '7 days' AS retake_deadline -- Прибавляет к дате оценки 7 дней и показывает полученную дату.
FROM grades
WHERE grade_date >= '2026-09-01' -- Оставляет оценки, поставленные 1 сентября 2026 года или позже.
ORDER BY grade_date; -- Сортирует оценки по дате от ранней к поздней.

-- 5. Строковые функции (LOWER, LENGTH) + WHERE
SELECT 
    subject_name,
    LOWER(subject_name) AS lower_subject, -- LOWER переводит название предмета в нижний регистр.
    LENGTH(subject_name) AS name_length -- LENGTH считает количество символов в названии предмета.
FROM subjects
WHERE LENGTH(subject_name) > 6; -- Оставляет только названия длиннее 6 символов.

-- АГРЕГАТНЫЕ ФУНКЦИИ (COUNT, SUM, AVG, MIN, MAX) с GROUP BY и HAVING

-- 6. COUNT: Количество учеников в каждом классе
SELECT 
    class_id,
    COUNT(student_id) AS total_students -- COUNT считает учеников в группе, не считая значения NULL.
FROM students
GROUP BY class_id -- Объединяет учеников в группы по классу.
HAVING COUNT(student_id) >= 1; -- Оставляет группы, в которых посчитан хотя бы один ученик.

-- 7. AVG: Средняя оценка по каждому предмету
SELECT 
    subject_id,
    ROUND(AVG(grade), 2) AS average_grade -- AVG считает среднюю оценку; ROUND округляет ее до 2 знаков после запятой.
FROM grades
GROUP BY subject_id -- Объединяет оценки по предметам.
HAVING AVG(grade) >= 8; -- Оставляет предметы со средней оценкой не ниже 8.

-- 8. MAX: Максимальная оценка ученика
SELECT 
    student_id,
    MAX(grade) AS max_grade -- MAX находит наибольшую оценку в группе.
FROM grades
GROUP BY student_id -- Объединяет оценки по ученикам.
HAVING MAX(grade) >= 9; -- Оставляет учеников, у которых есть оценка не ниже 9.

-- 9. MIN: Минимальная оценка по предметам
SELECT 
    subject_id,
    MIN(grade) AS min_grade -- MIN находит наименьшую оценку в группе.
FROM grades
GROUP BY subject_id -- Объединяет оценки по предметам.
HAVING MIN(grade) <= 8; -- Оставляет предметы, где есть оценка не выше 8.

-- 10. SUM: Общая сумма «баллов/оценок» по предметам (для примера использования SUM)
SELECT 
    subject_id,
    SUM(grade) AS sum_grades -- SUM складывает все оценки в группе.
FROM grades
GROUP BY subject_id -- Объединяет оценки по предметам.
HAVING SUM(grade) > 5; -- Оставляет предметы, у которых сумма оценок больше 5.