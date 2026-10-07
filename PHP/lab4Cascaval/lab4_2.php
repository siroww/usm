<?php

declare(strict_types=1);

$dir = 'image/';
$files = scandir($dir);
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>About Cats</title>
    <style>
        body {
            font-family: monospace, sans-serif;
            margin: 20px auto;
            max-width: 800px;
            color: #333;
        }
        header {
            border: 1px solid #000;
            padding: 10px 15px;
            font-weight: bold;
            margin-bottom: 20px;
        }
        nav a {
            text-decoration: none;
            color: #000;
            margin-right: 15px;
        }
        h1 {
            margin: 10px 0 5px 0;
            font-size: 24px;
        }
        .subtitle {
            color: #aaa;
            margin-bottom: 20px;
        }
        .gallery {
            display: grid;
            grid-template-columns: repeat(3, 1fr);
            gap: 15px;
        }
        .gallery img {
            width: 100%;
            height: 220px;
            object-fit: cover;
            border-radius: 6px;
            border: 1px solid #ddd;
        }
        footer {
            text-align: center;
            margin-top: 30px;
            font-weight: bold;
            font-size: 14px;
        }
    </style>
</head>
<body>

    <header>
        <nav>
            <a href="#">About Cats</a> | 
            <a href="#">News</a> | 
            <a href="#">Contacts</a>
        </nav>
    </header>

    <main>
        <h1>#cats</h1>
        <div class="subtitle">Explore a world of cats</div>

        <div class="gallery">
            <?php
            if ($files !== false) {
                for ($i = 0; $i < count($files); $i++) {
                    if ($files[$i] !== "." && $files[$i] !== "..") {
                        $path = $dir . $files[$i];
                        // Проверяем расширение файла (.jpg или .jpeg)
                        if (preg_match('/\.(jpg|jpeg|png|gif)$/i', $files[$i])) {
                            echo '<img src="' . htmlspecialchars($path) . '" alt="Cat Image">';
                        }
                    }
                }
            }
            ?>
        </div>
    </main>

    <footer>
        USM © <?= date('Y') ?>
    </footer>

</body>
</html>