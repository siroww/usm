// Собственное проверяемое исключение для ошибок ввода данных компьютера.
public class PCException extends Exception {
    private static final long serialVersionUID = 1L;

    private final boolean recoverable;

    // Создаёт ошибку, после которой можно повторить ввод.
    public PCException(String message) {
        this(message, null, true);
    }

    // Создаёт ошибку преобразования и сохраняет исходную стандартную ошибку.
    public PCException(String message, Throwable cause) {
        this(message, cause, true);
    }

    // Создаёт ошибку с указанием, можно ли продолжить ввод.
    public PCException(String message, boolean recoverable) {
        this(message, null, recoverable);
    }

    // Создаёт ошибку с исходной причиной и признаком возможности повтора.
    public PCException(String message, Throwable cause, boolean recoverable) {
        super(message, cause);
        this.recoverable = recoverable;
    }

    public static PCException emptyString() {
        return new PCException("Строка не должна быть пустой.");
    }

    public static PCException invalidComponentCount() {
        return new PCException("Количество деталей должно быть от 1 до 127.");
    }

    public static PCException componentCountMustBeInteger(Throwable cause) {
        return new PCException("Количество деталей должно быть целым числом.", cause);
    }

    public static PCException numberRequired(Throwable cause) {
        return new PCException("Нужно ввести число.", cause);
    }

    public static PCException valueOutOfRange(float minimum, float maximum, boolean includeMinimum) {
        String minimumRule = includeMinimum ? "не меньше " : "больше ";
        return new PCException("Значение должно быть " + minimumRule + minimum
                + " и не больше " + maximum + ".");
    }

    // Выводит сообщение об ошибке
    public void prelucrare() {
        System.err.println("Ошибка ввода: " + getMessage());
    }

    // Показывает, следует ли повторить запрос после ошибки.
    public boolean isRecoverable() {
        return recoverable;
    }
}
