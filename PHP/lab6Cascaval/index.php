<?php
require_once 'classes.php';

$repo = new ItemRepository('data.json');
$items = $repo->getAll();

// 1. Поиск по названию
$searchName = $_GET['search_name'] ?? '';
if ($searchName !== '') {
    $items = array_filter($items, fn(Item $i) => mb_stripos($i->getTitle(), $searchName) !== false);
}

// 2. Поиск по цене (промежуток)
$priceMin = (isset($_GET['price_min']) && $_GET['price_min'] !== '') ? floatval($_GET['price_min']) : null;
$priceMax = (isset($_GET['price_max']) && $_GET['price_max'] !== '') ? floatval($_GET['price_max']) : null;

if ($priceMin !== null) {
    $items = array_filter($items, fn(Item $i) => $i->getPrice() >= $priceMin);
}
if ($priceMax !== null) {
    $items = array_filter($items, fn(Item $i) => $i->getPrice() <= $priceMax);
}

// 3. Сортировка
$sort = $_GET['sort'] ?? 'title_asc';
usort($items, function(Item $a, Item $b) use ($sort) {
    if ($sort === 'price_asc') return $a->getPrice() <=> $b->getPrice();
    if ($sort === 'price_desc') return $b->getPrice() <=> $a->getPrice();
    if ($sort === 'date_asc') return strcmp($a->getTargetDate(), $b->getTargetDate());
    if ($sort === 'date_desc') return strcmp($b->getTargetDate(), $a->getTargetDate());
    return strcmp($a->getTitle(), $b->getTitle());
});

// Первые 3 карточки
$topThree = array_slice($items, 0, 3);
?>
<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <title>Главная страница</title>
</head>
<body>
    <h1>Главная страница каталога</h1>
    <a href="admin.php">Перейти в админку</a>
    <hr>

    <!-- Форма поиска и сортировки -->
    <form method="GET" action="index.php">
        <p>
            Поиск по названию: 
            <input type="text" name="search_name" value="<?= htmlspecialchars($searchName) ?>">
        </p>
        <p>
            Цена от: <input type="number" step="0.01" name="price_min" value="<?= htmlspecialchars($_GET['price_min'] ?? '') ?>">
            до: <input type="number" step="0.01" name="price_max" value="<?= htmlspecialchars($_GET['price_max'] ?? '') ?>">
        </p>
        <p>
            Сортировка:
            <select name="sort">
                <option value="title_asc" <?= $sort === 'title_asc' ? 'selected' : '' ?>>По названию (А-Я)</option>
                <option value="price_asc" <?= $sort === 'price_asc' ? 'selected' : '' ?>>Сначала дешевые</option>
                <option value="price_desc" <?= $sort === 'price_desc' ? 'selected' : '' ?>>Сначала дорогие</option>
                <option value="date_asc" <?= $sort === 'date_asc' ? 'selected' : '' ?>>Сначала старые по дате</option>
                <option value="date_desc" <?= $sort === 'date_desc' ? 'selected' : '' ?>>Сначала новые по дате</option>
            </select>
        </p>
        <button type="submit">Применить</button>
        <a href="index.php">Сбросить</a>
    </form>
    <hr>

    <!-- Первые 3 карточки -->
    <h2>Первые 3 карточки</h2>
    <?php if (empty($topThree)): ?>
        <p>Нет карточек.</p>
    <?php else: ?>
        <div style="display: flex; gap: 15px;">
            <?php foreach ($topThree as $card): ?>
                <div style="border: 1px solid #999; padding: 10px; width: 220px;">
                    <h3><?= $card->getTitle() ?></h3>
                    <p><?= $card->getDescription() ?></p>
                    <p><b>Категория:</b> <?= $card->getCategory() ?></p>
                    <p><b>Дата:</b> <?= $card->getTargetDate() ?></p>
                    <p><b>Цена:</b> <?= $card->getPrice() ?> руб.</p>
                </div>
            <?php endforeach; ?>
        </div>
    <?php endif; ?>

    <hr>

    <!-- Все карточки в таблице -->
    <h2>Все карточки</h2>
    <table border="1" cellpadding="5" cellspacing="0">
        <tr>
            <th>Название</th>
            <th>Описание</th>
            <th>Категория</th>
            <th>Статус</th>
            <th>Дата</th>
            <th>Цена</th>
        </tr>
        <?php if (empty($items)): ?>
            <tr><td colspan="6">Ничего не найдено</td></tr>
        <?php else: ?>
            <?php foreach ($items as $item): ?>
                <tr>
                    <td><?= $item->getTitle() ?></td>
                    <td><?= $item->getDescription() ?></td>
                    <td><?= $item->getCategory() ?></td>
                    <td><?= $item->getStatus() ?></td>
                    <td><?= $item->getTargetDate() ?></td>
                    <td><?= $item->getPrice() ?> руб.</td>
                </tr>
            <?php endforeach; ?>
        <?php endif; ?>
    </table>
</body>
</html>