<?php
declare(strict_types=1);

require_once __DIR__ . '/Transaction.php';

/** Формирует HTML-таблицу транзакций. */
final class TransactionTableRenderer
{
    /**
     * Создаёт HTML-таблицу из списка транзакций.
     *
     * @param Transaction[] $transactions Транзакции для вывода.
     * @param bool $showDeleteButton Добавлять ли кнопку удаления в каждую строку.
     * @return string HTML-код таблицы.
     */
    public function render(array $transactions, bool $showDeleteButton = false): string
    {
        $html = '<table border="1" cellpadding="8" cellspacing="0" style="border-collapse: collapse; font-family: sans-serif;">';
        $html .= '<thead>';
        $html .= '<tr style="background-color: #f2f2f2;">';
        $html .= '<th>ID транзакции</th>';
        $html .= '<th>Дата</th>';
        $html .= '<th>Сумма</th>';
        $html .= '<th>Описание</th>';
        $html .= '<th>Название получателя</th>';
        $html .= '<th>Категория получателя</th>';
        $html .= '<th>Количество дней с момента транзакции</th>';
        if ($showDeleteButton) {
            $html .= '<th>Действие</th>';
        }
        $html .= '</tr>';
        $html .= '</thead>';
        $html .= '<tbody>';

        if (empty($transactions)) {
            $columnCount = $showDeleteButton ? 8 : 7;
            $html .= '<tr><td colspan="' . $columnCount . '" style="text-align: center;">Нет данных о транзакциях</td></tr>';
        } else {
            foreach ($transactions as $transaction) {
                $html .= '<tr>';
                $html .= '<td>' . htmlspecialchars((string) $transaction->getId()) . '</td>';
                $html .= '<td>' . htmlspecialchars($transaction->getDate()) . '</td>';
                $html .= '<td>' . number_format($transaction->getAmount(), 2, '.', ' ') . ' MDL</td>';
                $html .= '<td>' . htmlspecialchars($transaction->getDescription()) . '</td>';
                $html .= '<td>' . htmlspecialchars($transaction->getMerchant()) . '</td>';
                $html .= '<td>' . htmlspecialchars($transaction->getCategory()) . '</td>';
                $html .= '<td>' . $transaction->getDaysSinceTransaction() . ' дн.</td>';
                if ($showDeleteButton) {
                    $html .= '<td><form method="post">'
                        . '<input type="hidden" name="action" value="delete">'
                        . '<input type="hidden" name="id" value="' . $transaction->getId() . '">'
                        . '<button type="submit">Удалить</button>'
                        . '</form></td>';
                }
                $html .= '</tr>';
            }
        }

        $html .= '</tbody>';
        $html .= '</table>';

        return $html;
    }
}