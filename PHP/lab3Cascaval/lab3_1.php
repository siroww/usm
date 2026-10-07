<?php
// Получаем текущий день недели (1 - понедельник, ..., 7 - воскресенье)
$dayOfWeek = (int)date('N');

// График для John Styles (понедельник (1), среда (3), пятница (5))
if ($dayOfWeek == 1 || $dayOfWeek == 3 || $dayOfWeek == 5) {
    $johnSchedule = "8:00-12:00";
} else {
    $johnSchedule = "Нерабочий день";
}

// График для Jane Doe (вторник (2), четверг (4), суббота (6))
if ($dayOfWeek == 2 || $dayOfWeek == 4 || $dayOfWeek == 6) {
    $janeSchedule = "12:00-16:00";
} else {
    $janeSchedule = "Нерабочий день";
}
?>

<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <title>Расписание работы</title>
    <style>
        table { border-collapse: collapse; width: 50%; font-family: Arial, sans-serif; }
        th, td { border: 1px solid #ddd; padding: 8px; text-align: left; }
        th { background-color: #f2f2f2; }
    </style>
</head>
<body>

    <h3>Расписание на сегодня (День недели: <?php echo date('l'); ?>)</h3>
    <table>
        <tr>
            <th>№</th>
            <th>Фамилия Имя</th>
            <th>График работы</th>
        </tr>
        <tr>
            <td>1</td>
            <td>John Styles</td>
            <td><?php echo $johnSchedule; ?></td>
        </tr>
        <tr>
            <td>2</td>
            <td>Jane Doe</td>
            <td><?php echo $janeSchedule; ?></td>
        </tr>
    </table>

</body>
</html>