<?php
declare(strict_types=1);

require_once __DIR__ . '/Transaction.php';
require_once __DIR__ . '/TransactionRepository.php';
require_once __DIR__ . '/TransactionManager.php';
require_once __DIR__ . '/TransactionTableRenderer.php';

$repository = new TransactionRepository(__DIR__ . '/transactions.txt');

// Добавляем примеры при первом запуске.
if (!is_file(__DIR__ . '/transactions.txt')) {
    foreach ([
        new Transaction(1, '2026-01-10', 1500.50, 'Покупка продуктов', 'Linella', 'Продукты'),
        new Transaction(2, '2026-02-15', 350.00, 'Мобильная связь', 'Orange', 'Связь'),
        new Transaction(3, '2026-03-01', 12000.00, 'Аренда квартиры', 'Иван Петров', 'Недвижимость'),
        new Transaction(4, '2026-03-12', 450.75, 'Кофе и выпечка', 'Starbucks', 'Кафе'),
        new Transaction(5, '2026-04-05', 2500.00, 'Кроссовки', 'Nike', 'Одежда'),
        new Transaction(6, '2026-05-20', 180.00, 'Поездка на такси', 'Yango', 'Транспорт'),
        new Transaction(7, '2026-06-11', 8900.00, 'Монитор', 'Maximum', 'Электроника'),
        new Transaction(8, '2026-07-02', 650.00, 'Ужин', 'Draft', 'Кафе'),
        new Transaction(9, '2026-08-19', 3200.00, 'Книги', 'Librarius', 'Образование'),
        new Transaction(10, '2026-09-01', 540.00, 'Бензин', 'Vento', 'Транспорт'),
    ] as $transaction) {
        $repository->addTransaction($transaction);
    }
}

$manager = new TransactionManager($repository);
$renderer = new TransactionTableRenderer();
$error = '';

// Добавляем или удаляем транзакцию. Репозиторий сам сохраняет изменения в файл.
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    if (($_POST['action'] ?? '') === 'delete') {
        $repository->removeTransactionById((int) ($_POST['id'] ?? 0));
    } elseif (($_POST['action'] ?? '') === 'add') {
        $date = (string) ($_POST['date'] ?? '');
        $amount = (string) ($_POST['amount'] ?? '');
        $description = trim((string) ($_POST['description'] ?? ''));
        $merchant = trim((string) ($_POST['merchant'] ?? ''));
        $category = trim((string) ($_POST['category'] ?? 'Разное'));

        if ($date === '' || !is_numeric($amount) || $description === '' || $merchant === '') {
            $error = 'Заполните все обязательные поля.';
        } else {
            $ids = array_map(
                static fn(Transaction $transaction): int => $transaction->getId(),
                $repository->getAllTransactions()
            );
            $id = $ids === [] ? 1 : max($ids) + 1;
            $repository->addTransaction(new Transaction(
                $id,
                $date,
                (float) $amount,
                $description,
                $merchant,
                $category
            ));
        }
    }

    if ($error === '') {
        header('Location: index.php');
        exit;
    }
}

$date = (string) ($_GET['date'] ?? '');
$searchId = isset($_GET['id']) && is_string($_GET['id']) ? $_GET['id'] : '';
$transactions = $repository->getAllTransactions();

// Ищем одну транзакцию по ID, если ID введён.
if ($searchId !== '') {
    $id = filter_var($searchId, FILTER_VALIDATE_INT);
    if ($id === false || $id < 1) {
        $error = 'Введите корректный ID транзакции.';
        $transactions = [];
    } else {
        $transaction = $repository->findById($id);
        $transactions = $transaction === null ? [] : [$transaction];
    }
} elseif ($date !== '') {
    $transactions = $manager->findTransactionsByDate($date);
}

if (($_GET['sort'] ?? 'desc') === 'asc') {
    $transactions = $manager->sortTransactionsByAmountAsc($transactions);
} else {
    $transactions = $manager->sortTransactionsByAmountDesc($transactions);
}
?>
<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <title>Банковские транзакции</title>
</head>
<body>
    <h1>Банковские транзакции</h1>

    <?php if ($error !== ''): ?>
        <p><?= htmlspecialchars($error, ENT_QUOTES, 'UTF-8') ?></p>
    <?php endif; ?>

    <h2>Добавить транзакцию</h2>
    <form method="post">
        <input type="hidden" name="action" value="add">
        Дата: <input type="date" name="date" required>
        Сумма: <input type="number" name="amount" min="0.01" step="0.01" required>
        Описание: <input type="text" name="description" required>
        Получатель: <input type="text" name="merchant" required>
        Категория: <input type="text" name="category">
        <button>Добавить</button>
    </form>

    <h2>Поиск по дате</h2>
    <form method="get">
        <input type="date" name="date" value="<?= htmlspecialchars($date, ENT_QUOTES, 'UTF-8') ?>">
        <input type="hidden" name="sort" value="<?= htmlspecialchars((string) ($_GET['sort'] ?? 'desc'), ENT_QUOTES, 'UTF-8') ?>">
        <button>Найти</button>
        <a href="index.php">Сбросить</a>
    </form>

    <h2>Поиск по айди</h2>
    <form method="get">
        <input type="number" name="id" min="1" value="<?= htmlspecialchars($searchId, ENT_QUOTES, 'UTF-8') ?>">
        <input type="hidden" name="sort" value="<?= htmlspecialchars((string) ($_GET['sort'] ?? 'desc'), ENT_QUOTES, 'UTF-8') ?>">
        <button>Найти</button>
        <a href="index.php">Сбросить</a>
    </form>

    <form method="get">
        <input type="hidden" name="date" value="<?= htmlspecialchars($date, ENT_QUOTES, 'UTF-8') ?>">
        <input type="hidden" name="id" value="<?= htmlspecialchars($searchId, ENT_QUOTES, 'UTF-8') ?>">
        <button name="sort" value="asc">Меньше → больше</button>
        <button name="sort" value="desc">Больше → меньше</button>
    </form>

    <h2>Транзакции</h2>
    <?= $renderer->render($transactions, true) ?>

    <h2>Вычисления</h2>
    <p>Общая сумма: <?= number_format($manager->calculateTotalAmount(), 2) ?> MDL</p>
    <p>Транзакций у Maximum: <?= $manager->countTransactionsByMerchant('Maximum') ?></p>
</body>
</html>
