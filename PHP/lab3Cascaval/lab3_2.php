<?php
$a = 0;
$b = 0;

for ($i = 0; $i <= 5; $i++) {
   $a += 10;
   $b += 5;
   echo "Шаг $i: a = $a, b = $b<br>";
}

echo "<strong>End of the loop: a = $a, b = $b</strong>";
?>