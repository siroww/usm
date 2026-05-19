from flask import Flask, render_template, request, redirect, url_for, flash, abort
import sqlite3
import os
from datetime import datetime

# Создание Flask-приложения и настройка секретного ключа для flash-сообщений
app = Flask(__name__)
app.secret_key = '123'

# Путь к файлу базы данных SQLite
DB_PATH = os.path.join(os.path.dirname(__file__), 'database.db')


def get_db():
    # Возвращает соединение с базой данных и настраивает доступ к строкам как словарям
    conn = sqlite3.connect(DB_PATH)
    conn.row_factory = sqlite3.Row
    return conn


def init_db():
    # Создает таблицу books, если она еще не существует, и заполняет примерами
    with get_db() as conn:
        conn.execute('''
            CREATE TABLE IF NOT EXISTS books (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                title TEXT NOT NULL,
                author TEXT NOT NULL,
                genre TEXT NOT NULL,
                pages INTEGER NOT NULL,
                rating REAL NOT NULL,
                created_at TEXT NOT NULL,
                status TEXT NOT NULL DEFAULT 'Хочу прочитать',
                notes TEXT DEFAULT ''
            )
        ''')
        existing_columns = [row[1] for row in conn.execute("PRAGMA table_info(books)").fetchall()]
        if 'status' not in existing_columns:
            conn.execute("ALTER TABLE books ADD COLUMN status TEXT NOT NULL DEFAULT 'Хочу прочитать'")
        if 'notes' not in existing_columns:
            conn.execute("ALTER TABLE books ADD COLUMN notes TEXT DEFAULT ''")

        count = conn.execute('SELECT COUNT(*) FROM books').fetchone()[0]
        if count == 0:
            sample = [
                ('Мастер и Маргарита', 'Михаил Булгаков', 'Роман', 480, 9.5, '2024-01-10', 'Прочитано', 'Классика, которую стоит перечитать.'),
                ('1984', 'Джордж Оруэлл', 'Антиутопия', 328, 9.2, '2024-02-14', 'Прочитано', 'Мрачное и сильное произведение.'),
                ('Преступление и наказание', 'Фёдор Достоевский', 'Классика', 672, 8.9, '2024-03-01', 'Читаю', 'Медленный, но глубокий роман.'),
                ('Маленький принц', 'Антуан де Сент-Экзюпери', 'Философия', 96, 9.8, '2024-03-20', 'Прочитано', 'Отличная книга для всех возрастов.'),
                ('Гарри Поттер и философский камень', 'Дж. К. Роулинг', 'Фэнтези', 432, 9.1, '2024-04-05', 'Хочу прочитать', 'Начало волшебной серии.'),
            ]
            conn.executemany(
                'INSERT INTO books (title, author, genre, pages, rating, created_at, status, notes) VALUES (?,?,?,?,?,?,?,?)',
                sample
            )
            conn.commit()


# Маршруты

@app.route('/')
def index():
    # Главная страница показывает последние добавленные книги и общее количество книг
    with get_db() as conn:
        recent = conn.execute(
            'SELECT * FROM books ORDER BY created_at DESC LIMIT 2'
        ).fetchall()
        total = conn.execute('SELECT COUNT(*) FROM books').fetchone()[0]
    return render_template('index.html', recent=recent, total=total)


@app.route('/books')
def books():
    # Страница списка книг с выбором жанра, статуса, поиска и сортировки
    genre_filter = request.args.get('genre', '')
    status_filter = request.args.get('status', '')
    search_query = request.args.get('q', '').strip()
    sort_by = request.args.get('sort', 'created_at')
    order = request.args.get('order', 'desc')

    allowed_sorts = {'title', 'author', 'genre', 'pages', 'rating', 'created_at', 'status'}
    if sort_by not in allowed_sorts:
        sort_by = 'created_at'
    direction = 'DESC' if order == 'desc' else 'ASC'

    with get_db() as conn:
        genres = [r[0] for r in conn.execute('SELECT DISTINCT genre FROM books ORDER BY genre').fetchall()]
        statuses = ['Прочитано', 'Читаю', 'Хочу прочитать']

        query = 'SELECT * FROM books'
        where_clauses = []
        params = []

        if genre_filter:
            where_clauses.append('genre=?')
            params.append(genre_filter)
        if status_filter:
            where_clauses.append('status=?')
            params.append(status_filter)
        if search_query:
            where_clauses.append('(title LIKE ? OR author LIKE ?)')
            params.extend([f'%{search_query}%', f'%{search_query}%'])

        if where_clauses:
            query += ' WHERE ' + ' AND '.join(where_clauses)

        query += f' ORDER BY {sort_by} {direction}'
        rows = conn.execute(query, params).fetchall()

    return render_template('books.html', books=rows, genres=genres,
                           statuses=statuses, genre_filter=genre_filter,
                           status_filter=status_filter, search_query=search_query,
                           sort_by=sort_by, order=order)


@app.route('/books/<int:book_id>')
def book_detail(book_id):
    # Страница информации по одной книге
    with get_db() as conn:
        book = conn.execute('SELECT * FROM books WHERE id=?', (book_id,)).fetchone()
    if book is None:
        abort(404)
    return render_template('book_detail.html', book=book)


@app.route('/add', methods=['GET', 'POST'])
def add_book():
    # Обработка формы добавления новой книги
    errors = {}
    form_data = {}
    status_options = ['Прочитано', 'Читаю', 'Хочу прочитать']

    if request.method == 'POST':
        form_data = {
            'title': request.form.get('title', '').strip(),
            'author': request.form.get('author', '').strip(),
            'genre': request.form.get('genre', '').strip(),
            'pages': request.form.get('pages', '').strip(),
            'rating': request.form.get('rating', '').strip(),
            'status': request.form.get('status', '').strip(),
            'notes': request.form.get('notes', '').strip(),
        }

        # Валидация
        if not form_data['title']:
            errors['title'] = 'Название не может быть пустым'
        elif len(form_data['title']) > 200:
            errors['title'] = 'Слишком длинное название (макс. 200 символов)'

        if not form_data['author']:
            errors['author'] = 'Укажите автора'

        if not form_data['genre']:
            errors['genre'] = 'Укажите жанр'

        if form_data['status'] not in status_options:
            errors['status'] = 'Выберите корректный статус книги'

        try:
            pages = int(form_data['pages'])
            if pages <= 0:
                errors['pages'] = 'Количество страниц должно быть больше 0'
        except ValueError:
            errors['pages'] = 'Количество страниц должно быть целым числом'

        try:
            rating = float(form_data['rating'])
            if not (0 <= rating <= 10):
                errors['rating'] = 'Рейтинг должен быть от 0 до 10'
        except ValueError:
            errors['rating'] = 'Рейтинг должен быть числом'

        if not errors:
            created_at = datetime.now().strftime('%Y-%m-%d')
            with get_db() as conn:
                conn.execute(
                    'INSERT INTO books (title, author, genre, pages, rating, created_at, status, notes) VALUES (?,?,?,?,?,?,?,?)',
                    (form_data['title'], form_data['author'], form_data['genre'],
                     pages, rating, created_at, form_data['status'], form_data['notes'])
                )
                conn.commit()
            flash('Книга успешно добавлена!', 'success')
            return redirect(url_for('books'))

    return render_template('add_book.html', errors=errors, form_data=form_data, status_options=status_options)


@app.route('/books/<int:book_id>/edit', methods=['GET', 'POST'])
def edit_book(book_id):
    # Обработка редактирования выбранной книги
    with get_db() as conn:
        book = conn.execute('SELECT * FROM books WHERE id=?', (book_id,)).fetchone()
    if book is None:
        abort(404)

    errors = {}
    form_data = dict(book)
    status_options = ['Прочитано', 'Читаю', 'Хочу прочитать']

    if request.method == 'POST':
        form_data = {
            'title': request.form.get('title', '').strip(),
            'author': request.form.get('author', '').strip(),
            'genre': request.form.get('genre', '').strip(),
            'pages': request.form.get('pages', '').strip(),
            'rating': request.form.get('rating', '').strip(),
            'status': request.form.get('status', '').strip(),
            'notes': request.form.get('notes', '').strip(),
        }

        if not form_data['title']:
            errors['title'] = 'Название не может быть пустым'
        if not form_data['author']:
            errors['author'] = 'Укажите автора'
        if not form_data['genre']:
            errors['genre'] = 'Укажите жанр'
        if form_data['status'] not in status_options:
            errors['status'] = 'Выберите корректный статус книги'

        try:
            pages = int(form_data['pages'])
            if pages <= 0:
                errors['pages'] = 'Количество страниц должно быть больше 0'
        except ValueError:
            errors['pages'] = 'Количество страниц должно быть целым числом'

        try:
            rating = float(form_data['rating'])
            if not (0 <= rating <= 10):
                errors['rating'] = 'Рейтинг должен быть от 0 до 10'
        except ValueError:
            errors['rating'] = 'Рейтинг должен быть числом'

        if not errors:
            with get_db() as conn:
                conn.execute(
                    'UPDATE books SET title=?, author=?, genre=?, pages=?, rating=?, status=?, notes=? WHERE id=?',
                    (form_data['title'], form_data['author'], form_data['genre'],
                     pages, rating, form_data['status'], form_data['notes'], book_id)
                )
                conn.commit()
            flash('Книга обновлена!', 'success')
            return redirect(url_for('book_detail', book_id=book_id))

    return render_template('edit_book.html', book=book, errors=errors, form_data=form_data, status_options=status_options)


@app.route('/books/<int:book_id>/delete', methods=['POST'])
def delete_book(book_id):
    # Удаляет книгу из базы данных по id
    with get_db() as conn:
        book = conn.execute('SELECT * FROM books WHERE id=?', (book_id,)).fetchone()
        if book is None:
            abort(404)
        conn.execute('DELETE FROM books WHERE id=?', (book_id,))
        conn.commit()
    flash('Книга удалена.', 'info')
    return redirect(url_for('books'))


@app.route('/stats')
def stats():
    # Страница статистики по книгам: средние оценки, жанры и топ-5
    with get_db() as conn:
        total = conn.execute('SELECT COUNT(*) FROM books').fetchone()[0]
        avg_rating = conn.execute('SELECT ROUND(AVG(rating),2) FROM books').fetchone()[0]
        avg_pages = conn.execute('SELECT ROUND(AVG(pages),0) FROM books').fetchone()[0]
        max_rating = conn.execute('SELECT title, rating FROM books ORDER BY rating DESC LIMIT 1').fetchone()
        by_genre = conn.execute(
            'SELECT genre, COUNT(*) as cnt, ROUND(AVG(rating),2) as avg_r FROM books GROUP BY genre ORDER BY cnt DESC'
        ).fetchall()
        top_books = conn.execute('SELECT * FROM books ORDER BY rating DESC LIMIT 5').fetchall()

    return render_template('stats.html', total=total, avg_rating=avg_rating,
                           avg_pages=avg_pages, max_rating=max_rating,
                           by_genre=by_genre, top_books=top_books)



if __name__ == '__main__':
    init_db()
    app.run(debug=True)
