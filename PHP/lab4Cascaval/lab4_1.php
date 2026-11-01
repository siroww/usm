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

    // Возвращаем первый элемент отфильтрованного массива или null, если он пуст
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
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Система управления банковскими транзакциями</title>
    <style>
        :root {
            --primary-color: #2563eb;
            --primary-hover: #1d4ed8;
            --bg-color: #f8fafc;
            --card-bg: #ffffff;
            --text-color: #1e293b;
            --border-color: #e2e8f0;
        }

        body {
            font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif;
            background-color: var(--bg-color);
            color: var(--text-color);
            margin: 0;
            padding: 30px;
        }

        .container {
            max-width: 1000px;
            margin: 0 auto;
            background: var(--card-bg);
            padding: 30px;
            border-radius: 12px;
            box-shadow: 0 4px 6px -1px rgb(0 0 0 / 0.1), 0 2px 4px -2px rgb(0 0 0 / 0.1);
        }

        h2 {
            margin-top: 0;
            font-size: 24px;
            color: #0f172a;
            margin-bottom: 20px;
            border-bottom: 2px solid var(--border-color);
            padding-bottom: 12px;
        }

        .search-box {
            margin-bottom: 20px;
        }

        .search-box input {
            width: 100%;
            max-width: 350px;
            padding: 10px 14px;
            border: 1px solid var(--border-color);
            border-radius: 6px;
            font-size: 14px;
            outline: none;
            transition: border-color 0.2s;
        }

        .search-box input:focus {
            border-color: var(--primary-color);
            box-shadow: 0 0 0 3px rgba(37, 99, 235, 0.1);
        }

        .table-responsive {
            overflow-x: auto;
        }

        table {
            border-collapse: collapse;
            width: 100%;
            margin-top: 5px;
            font-size: 14px;
        }

        th, td {
            border: 1px solid var(--border-color);
            padding: 12px 16px;
            text-align: left;
        }

        th {
            background-color: #f1f5f9;
            font-weight: 600;
            color: #475569;
        }

        tbody tr:hover {
            background-color: #f8fafc;
        }

        tfoot tr {
            font-weight: bold;
            background-color: #f1f5f9;
        }

        .amount {
            font-weight: 600;
            color: #059669;
        }
    </style>
</head>
<body>

    <div class="container">
        <h2>Список транзакций</h2>

        <div class="search-box">
            <input type="text" id="searchInput" placeholder="Быстрый поиск по транзакциям..." onkeyup="filterTable()">
        </div>

        <div class="table-responsive">
            <table id="transactionsTable">
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
                            <td class="amount"><?= number_format($transaction['amount'], 2) ?></td>
                            <td><?= htmlspecialchars($transaction['description']) ?></td>
                            <td><?= htmlspecialchars($transaction['merchant']) ?></td>
                            <td><?= daysSinceTransaction($transaction['date']) ?></td>
                        </tr>
                    <?php endforeach; ?>
                </tbody>
                <tfoot>
                    <tr>
                        <td colspan="2">Итоговая сумма:</td>
                        <td colspan="4" class="amount"><?= number_format(calculateTotalAmount($transactions), 2) ?> $</td>
                    </tr>
                </tfoot>
            </table>
        </div>
    </div>

    <script>
        function filterTable() {
            const input = document.getElementById("searchInput");
            const filter = input.value.toLowerCase();
            const table = document.getElementById("transactionsTable");
            const trs = table.getElementsByTagName("tr");

            for (let i = 1; i < trs.length - 1; i++) { // Пропускаем заголовок и футер
                let visible = false;
                const tds = trs[i].getElementsByTagName("td");
                for (let j = 0; j < tds.length; j++) {
                    if (tds[j]) {
                        if (tds[j].innerHTML.toLowerCase().indexOf(filter) > -1) {
                            visible = true;
                            break;
                        }
                    }
                }
                trs[i].style.display = visible ? "" : "none";
            }
        }
    </script>

</body>
</html>