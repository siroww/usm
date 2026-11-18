<?php
require_once 'classes.php';

$repo = new ItemRepository('data.json');
$validator = new ItemValidator();
$errors = [];

// Удаление
if (isset($_GET['delete'])) {
    $repo->delete($_GET['delete']);
    header('Location: admin.php');
    exit;
}

// Редактирование (поиск по ID)
$editItem = null;
if (isset($_GET['edit'])) {
    $editItem = $repo->findById($_GET['edit']);
}

// Обработка отправки формы (POST)
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $errors = $validator->validate($_POST);
    if (empty($errors)) {
        $id = $_POST['id'] !== '' ? $_POST['id'] : uniqid();
        $title = htmlspecialchars(trim($_POST['title']));
        $description = htmlspecialchars(trim($_POST['description']));
        $category = $_POST['category'];
        $status = isset($_POST['status']) ? 'Да' : 'Нет';
        $targetDate = $_POST['target_date'];
        $price = floatval($_POST['price']);

        $existing = $repo->findById($id);
        $createdAt = $existing ? $existing->getCreatedAt() : date('Y-m-d H:i:s');

        $item = new Item($id, $title, $description, $category, $status, $targetDate, $price, $createdAt);

        if ($existing) {
            $repo->update($item);
        } else {
            $repo->add($item);
        }

        header('Location: admin.php');
        exit;
    }
}

$items = $repo->getAll();
?>
<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <title>Админ-панель</title>
</head>
<body>
    <h1>Админ-панель (ООП)</h1>
    <a href="index.php">← На главную страницу</a>
    <hr>

    <?php if (!empty($errors)): ?>
        <ul style="color: red;">
            <?php foreach ($errors as $error): ?>
                <li><?= $error ?></li>
            <?php endforeach; ?>
        </ul>
    <?php endif; ?>

    <h3><?= $editItem ? 'Редактировать карточку' : 'Добавить новую карточку' ?></h3>
    <form method="POST" action="admin.php">
        <input type="hidden" name="id" value="<?= $editItem ? $editItem->getId() : '' ?>">
        
        <p>
            Название:<br>
            <input type="text" name="title" required minlength="3" value="<?= $editItem ? $editItem->getTitle() : '' ?>">
        </p>
        <p>
            Описание:<br>
            <textarea name="description" required minlength="5"><?= $editItem ? $editItem->getDescription() : '' ?></textarea>
        </p>
        <p>
            Категория:<br>
            <select name="category" required>
                <?php $cat = $editItem ? $editItem->getCategory() : ''; ?>
                <option value="Работа" <?= $cat === 'Работа' ? 'selected' : '' ?>>Работа</option>
                <option value="Учеба" <?= $cat === 'Учеба' ? 'selected' : '' ?>>Учеба</option>
                <option value="Личное" <?= $cat === 'Личное' ? 'selected' : '' ?>>Личное</option>
            </select>
        </p>
        <p>
            <label>
                <input type="checkbox" name="status" value="1" <?= ($editItem && $editItem->getStatus() === 'Да') ? 'checked' : '' ?>>
                Статус (выполнено)
            </label>
        </p>
        <p>
            Дата:<br>
            <input type="date" name="target_date" required value="<?= $editItem ? $editItem->getTargetDate() : '' ?>">
        </p>
        <p>
            Цена:<br>
            <input type="number" step="0.01" name="price" required value="<?= $editItem ? $editItem->getPrice() : '' ?>">
        </p>

        <button type="submit">Сохранить</button>
        <?php if ($editItem): ?>
            <a href="admin.php">Отмена</a>
        <?php endif; ?>
    </form>

    <hr>
    <h3>Управление карточками</h3>
    <table border="1" cellpadding="5" cellspacing="0">
        <tr>
            <th>Название</th>
            <th>Описание</th>
            <th>Категория</th>
            <th>Статус</th>
            <th>Дата</th>
            <th>Цена</th>
            <th>Действия</th>
        </tr>
        <?php if (empty($items)): ?>
            <tr><td colspan="7">Нет карточек</td></tr>
        <?php else: ?>
            <?php foreach ($items as $item): ?>
                <tr>
                    <td><?= $item->getTitle() ?></td>
                    <td><?= $item->getDescription() ?></td>
                    <td><?= $item->getCategory() ?></td>
                    <td><?= $item->getStatus() ?></td>
                    <td><?= $item->getTargetDate() ?></td>
                    <td><?= $item->getPrice() ?> руб.</td>
                    <td>
                        <a href="admin.php?edit=<?= $item->getId() ?>">Изменить</a> | 
                        <a href="admin.php?delete=<?= $item->getId() ?>" onclick="return confirm('Точно удалить?')">Удалить</a>
                    </td>
                </tr>
            <?php endforeach; ?>
        <?php endif; ?>
    </table>
</body>
</html>