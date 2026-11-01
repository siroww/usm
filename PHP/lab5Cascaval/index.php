<?php
declare(strict_types=1);

// Подключаем необходимые файлы классов
require_once 'Transaction.php';
require_once 'TransactionStorageInterface.php';
require_once 'TransactionRepository.php';
require_once 'TransactionManager.php';
require_once 'TransactionTableRenderer.php';

// Создаем репозиторий и заполняем начальными данными
$repository = new TransactionRepository();

$initialTransactions = [
    new Transaction(1, '2026-01-10', 1500.50, 'Покупка продуктов', 'Supermarket Linella', 'Продукты'),
    new Transaction(2, '2026-02-15', 350.00, 'Оплата мобильной связи', 'Orange Moldova', 'Связь'),
    new Transaction(3, '2026-03-01', 12000.00, 'Аренда квартиры', 'Иван Петров', 'Недвижимость'),
    new Transaction(4, '2026-03-12', 450.75, 'Покупка кофе и выпечки', 'Starbucks', 'Кафе и рестораны'),
    new Transaction(5, '2026-04-05', 2500.00, 'Покупка кроссовок', 'Nike Store', 'Одежда'),
    new Transaction(6, '2026-05-20', 180.00, 'Поездка на такси', 'Yango', 'Транспорт'),
    new Transaction(7, '2026-06-11', 8900.00, 'Покупка монитора', 'Maximum', 'Электроника'),
    new Transaction(8, '2026-07-02', 650.00, 'Ужин в ресторане', 'Draft', 'Кафе и рестораны'),
    new Transaction(9, '2026-08-19', 3200.00, 'Покупка книг и учебников', 'Librarius', 'Образование'),
    new Transaction(10, '2026-09-01', 540.00, 'Заправка автомобиля', 'Vento', 'Транспорт'),
];

foreach ($initialTransactions as $tx) {
    $repository->addTransaction($tx);
}

// Инициализируем бизнес-логику и рендерер
$manager = new TransactionManager($repository);
$renderer = new TransactionTableRenderer();
?>
<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <title>Управление банковскими транзакциями</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 20px; color: #333; }
        h2 { border-bottom: 2px solid #ccc; padding-bottom: 5px; }
        .stats { background: #eef2f7; padding: 15px; border-radius: 5px; margin-bottom: 20px; }
    </style>
</head>
<body>

    <h1>Система управления банковскими транзакциями</h1>

    <div class="stats">
        <p><strong>Общая сумма всех транзакций:</strong> <?= number_format($manager->calculateTotalAmount(), 2, '.', ' ') ?> MDL</p>
        <p><strong>Сумма за период (2026-03-01 по 2026-06-30):</strong> <?= number_format($manager->calculateTotalAmountByDateRange('2026-03-01', '2026-06-30'), 2, '.', ' ') ?> MDL</p>
        <p><strong>Количество транзакций у получателя "Maximum":</strong> <?= $manager->countTransactionsByMerchant('Maximum') ?></p>
    </div>

    <h2>Все транзакции (отсортированные по сумме по убыванию)</h2>
    <?= $renderer->render($manager->sortTransactionsByAmountDesc()) ?>

</body>
</html>