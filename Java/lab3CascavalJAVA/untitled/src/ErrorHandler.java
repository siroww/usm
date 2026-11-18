import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.time.Year;
import java.util.List;

// Вспомогательные методы для получения текущего года и записи данных в файл.
public final class ErrorHandler {
    private ErrorHandler() {
    }

    // Возвращает текущий год для проверки года выпуска комплектующей.
    public static int getMaximumYear() {
        return Year.now().getValue();
    }

    // Записывает подготовленные строки в файл и сообщает об ошибке, если запись не удалась.
    public static void writeLines(String filename, List<String> lines) {
        try {
            Files.write(Paths.get(filename), lines);
            System.out.println("Данные объекта успешно сохранены в файл: " + filename);
        } catch (IOException e) {
            reportFileError(filename, e);
        }
    }

    // Выводит сообщение об ошибке сохранения файла.
    private static void reportFileError(String filename, IOException exception) {
        System.err.println("Ошибка при сохранении в файл " + filename + ": " + exception.getMessage());
    }
}
