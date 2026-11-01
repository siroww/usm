<?php
declare(strict_types=1);

require_once 'Transaction.php';

/**
 * Класс TransactionTableRenderer
 * Отвечает за генерацию HTML-представления таблицы транзакций.
 */

final class TransactionTableRenderer
{
    public function render(array $transactions): string
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
        $html .= '</tr>';
        $html .= '</thead>';
        $html .= '<tbody>';

        if (empty($transactions)) {
            $html .= '<tr><td colspan="7" style="text-align: center;">Нет данных о транзакциях</td></tr>';
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
                $html .= '</tr>';
            }
        }

        $html .= '</tbody>';
        $html .= '</table>';

        return $html;
    }
}