<?php

declare(strict_types=1);

/**
 * Исходный массив банковских транзакций.
 *
 * @var array<int, array{id: int, date: string, amount: float, description: string, merchant: string}>
 */
$transactions = [
    [
        "id" => 1,
        "date" => "2024-01-15",
        "amount" => 100.00,
        "description" => "Payment for groceries",
        "merchant" => "SuperMart",
    ],
    [
        "id" => 2,
        "date" => "2024-02-10",
        "amount" => 75.50,
        "description" => "Dinner with friends",
        "merchant" => "Local Restaurant",
    ],
    [
        "id" => 3,
        "date" => "2024-03-01",
        "amount" => 250.00,
        "description" => "Online store shopping",
        "merchant" => "TechShop",
    ],
    [
        "id" => 4,
        "date" => "2024-03-05",
        "amount" => 45.00,
        "description" => "Coffee and snacks",
        "merchant" => "CoffeeBean",
    ],
];

/**
 * Вычисляет общую сумму всех транзакций.
 *
 * @param array $transactions Массив транзакций.
 * @return float Общая сумма транзакций.
 */
function calculateTotalAmount(array $transactions): float
{
    $total = 0.0;
    foreach ($transactions as $transaction) {
        $total += $transaction['amount'];
    }
    return $total;
}

/**
 * Находит транзакции по части описания (поиск без учета регистра).
 *
 * @param string $descriptionPart Подстрока для поиска в описании.
 * @return array Массив найденных транзакций.
 */
function findTransactionByDescription(string $descriptionPart): array
{
    global $transactions;
    return array_filter($transactions, function (array $transaction) use ($descriptionPart): bool {
        return stripos($transaction['description'], $descriptionPart) !== false;
    });
}

/**
 * Находит транзакцию по её идентификатору с помощью цикла foreach.
 *
 * @param int $id Идентификатор транзакции.
 * @return array|null Возвращает массив с транзакцией или null, если не найдена.
 */
function findTransactionByIdForeach(int $id): ?array
{
    global $transactions;
    foreach ($transactions as $transaction) {
        if ($transaction['id'] === $id) {
            return $transaction;
        }
    }
    return null;
}

/**
 * Находит транзакцию по её идентификатору с помощью array_filter.
 *
 * @param int $id Идентификатор транзакции.
 * @return array|null Возвращает найденную транзакцию или null.
 */
function findTransactionById(int $id): ?array
{
    global $transactions;
    $result = array_filter($transactions, function (array $transaction) use ($id): bool {
        return $transaction['id'] === $id;
    });

    return !empty($result) ? reset($result) : null;
}

/**
 * Вычисляет количество дней между датой транзакции и текущим днём.
 *
 * @param string $date Дата транзакции в формате YYYY-MM-DD.
 * @return int Количество дней.
 */
function daysSinceTransaction(string $date): int
{
    $transactionDate = new DateTime($date);
    $currentDate = new DateTime();
    $interval = $transactionDate->diff($currentDate);
    return (int) $interval->format('%r%a');
}

/**
 * Добавляет новую транзакцию в глобальный массив $transactions.
 *
 * @param int $id Уникальный идентификатор транзакции.
 * @param string $date Дата транзакции (YYYY-MM-DD).
 * @param float $amount Сумма транзакции.
 * @param string $description Описание транзакции.
 * @param string $merchant Название организации.
 * @return void
 */
function addTransaction(int $id, string $date, float $amount, string $description, string $merchant): void
{
    global $transactions;
    $transactions[] = [
        "id" => $id,
        "date" => $date,
        "amount" => $amount,
        "description" => $description,
        "merchant" => $merchant,
    ];
}

// Добавление новой транзакции
addTransaction(5, "2024-03-20", 120.00, "Gas station fuel", "Shell");

// Сортировка транзакций по дате (от старых к новым)
usort($transactions, function (array $a, array $b): int {
    return strtotime($a['date']) <=> strtotime($b['date']);
});

?>
<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <title>Система управления банковскими транзакциями</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 20px; }
        table { border-collapse: collapse; width: 100%; margin-top: 15px; }
        th, td { border: 1px solid #ccc; padding: 10px; text-align: left; }
        th { background-color: #f4f4f4; }
        tfoot tr { font-weight: bold; background-color: #e9e9e9; }
    </style>
</head>
<body>

    <h2>Список транзакций</h2>

    <table>
        <thead>
            <tr>
                <th>ID</th>
                <th>Дата</th>
                <th>Сумма ($)</th>
                <th>Описание</th>
                <th>Организация (Merchant)</th>
                <th>Дней с момента транзакции</th>
            </tr>
        </thead>
        <tbody>
            <?php foreach ($transactions as $transaction): ?>
                <tr>
                    <td><?= htmlspecialchars((string)$transaction['id']) ?></td>
                    <td><?= htmlspecialchars($transaction['date']) ?></td>
                    <td><?= number_format($transaction['amount'], 2) ?></td>
                    <td><?= htmlspecialchars($transaction['description']) ?></td>
                    <td><?= htmlspecialchars($transaction['merchant']) ?></td>
                    <td><?= daysSinceTransaction($transaction['date']) ?></td>
                </tr>
            <?php endforeach; ?>
        </tbody>
        <tfoot>
            <tr>
                <td colspan="2">Итоговая сумма:</td>
                <td colspan="4"><?= number_format(calculateTotalAmount($transactions), 2) ?> $</td>
            </tr>
        </tfoot>
    </table>

</body>
</html>