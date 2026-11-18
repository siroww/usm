import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;

// Класс компьютера: хранит основные данные и список комплектующих.
public class PC {
    private static final BufferedReader KEYBOARD = new BufferedReader(new InputStreamReader(System.in));

    // Имя владельца или название компьютера.
    private String nickName;
    // Динамический список деталей компьютера.
    private ArrayList<PCPart> components;
    // Дополнительные характеристики компьютера.
    private int ID;
    private String color;
    private int power;
    private String operatingSystem;


    // Создаёт компьютер со стандартными значениями и пустым списком деталей.
    public PC() {
        this("NoName", new ArrayList<>(), 0, "NON-color", 0, "NON-OC");
    }

    // Создаёт компьютер и копирует переданный список комплектующих.
    public PC(String nickName, ArrayList<PCPart> components, int ID,
              String color, int power, String operatingSystem) {
        this.nickName = nickName;
        this.components = new ArrayList<>(components);
        this.ID = ID;
        this.color = color == null || color.trim().isEmpty() ? "NON-color" : color;
        this.power = power;
        this.operatingSystem = operatingSystem == null || operatingSystem.trim().isEmpty()
                ? "NON-OC"
                : operatingSystem;
        
    }

    // Создаёт независимую копию компьютера вместе с копиями его деталей.
    public PC(PC prototype) {
        this(prototype.nickName, new ArrayList<>(), prototype.ID, prototype.color,
                prototype.power, prototype.operatingSystem);
        prototype.components.forEach(component -> this.components.add(new PCPart(component)));
    }

    // Возвращает и изменяет имя компьютера.
    public String getNickName() {
        return nickName;
    }

    public void setNickName(String nickName) {
        this.nickName = nickName;
    }

    // Возвращает список деталей или заменяет его копией переданного списка.
    public ArrayList<PCPart> getComponents() {
        return components;
    }

    public void setComponents(ArrayList<PCPart> components) {
        this.components = new ArrayList<>(components);
    }

    // Возвращает и изменяет идентификатор компьютера.
    public int getID() {
        return ID;
    }

    public void setID(int ID) {
        this.ID = ID;
    }

    // Возвращает и изменяет цвет корпуса.
    public String getColor() {
        return color;
    }

    public void setColor(String color) {
        this.color = color;
    }

    // Возвращает и изменяет мощность компьютера.
    public int getPower() {
        return power;
    }

    public void setPower(int power) {
        this.power = power;
    }

    // Возвращает и изменяет название операционной системы.
    public String getOperatingSystem() {
        return operatingSystem;
    }

    public void setOperatingSystem(String operatingSystem) {
        this.operatingSystem = operatingSystem;
    }

    // Возвращает число созданных объектов компьютера.
    public int getCreatedCompsCount() {
        return components.size();
    }

    // Вводит имя компьютера и повторяет запрос, пока оно пустое или некорректное.
    public void inputNickName() throws PCException {
        nickName = readNonEmptyString("Введите имя компьютера: ");
    }

    // Запрашивает все данные компьютера и его комплектующих.
    public void readFromKeyboardPC() throws PCException {
        inputNickName();

        int componentCount = 0;
        boolean flag;
        // Ленивый способ обработки: ошибка передаётся вызывающему методу через throws.
        do {
            flag = false;
            try {
                System.out.print("Введите количество комплектующих (1-127): ");
                componentCount = readComponentCount();
            } catch (PCException e) {
                flag = e.isRecoverable();
                if (!e.isRecoverable()) {
                    throw e;
                }
                e.prelucrare();
            }
        } while (flag);

        ArrayList<PCPart> newComponents = new ArrayList<>();
        for (int i = 0; i < componentCount; i++) {
            System.out.println("\n--- Деталь #" + (i + 1) + " ---");
            String name = readNonEmptyString("Название модели: ");
            float weight = readCheckedFloat("Вес детали в кг (больше 0, не более 5): ", 0, 5, false);
            float year = readCheckedFloat(
                    "Год выпуска (1970-" + ErrorHandler.getMaximumYear() + "): ",
                    1970,
                    ErrorHandler.getMaximumYear(),
                    true
            );
            double price = readCheckedPrice("Цена детали (неотрицательное число): ");
            newComponents.add(new PCPart(name, weight, year, price));
        }
        components = newComponents;
    }

    // Первый способ обработки: метод сам ловит свою ошибку и повторяет ввод.
    // Флаг показывает, нужно ли повторять запрос после ошибки. Если ошибка неразрешимая, метод выбрасывает её вызывающему методу.
    // Через ду-цикл проверяет, что строка не пустая; если пустая, выбрасывает PCException.
    //Локальный цикл + самостоятельная обработка.
    private String readNonEmptyString(String prompt) throws PCException {
        boolean flag;
        String value = "";
        do {
            flag = false;
            try {
                System.out.print(prompt);
                value = readLine();
                if (value.trim().isEmpty()) {
                    throw PCException.emptyString();
                }
            } catch (PCException e) {
                flag = e.isRecoverable();
                if (!e.isRecoverable()) {
                    throw e;
                }
                e.prelucrare();
            }
        } while (flag);
        return value;
    }

    // Второй способ обработки: метод объявляет ошибку и передаёт её вызывающему методу.
    // В трай проверяет число и выбрасывает PCException, если оно некорректное.
    // Проверяет количество деталей; ошибку объявляет для обработки вызывающим методом.
    //Без циклов + проброс ошибки наверх (делегирование).
    private int readComponentCount() throws PCException {
        try {
            int value = Integer.parseInt(readLine());
            if (value < 1 || value > Byte.MAX_VALUE) {
                throw PCException.invalidComponentCount();
            }
            return value;
        } catch (NumberFormatException e) {
            throw PCException.componentCountMustBeInteger(e);
        }
    }

    // Третий способ обработки: вложенный try-catch преобразует ошибку числа в PCException.
    //Вложенный try-catch + цикл повтора + преобразование чужих ошибок.
    private float readCheckedFloat(String prompt, float minimum, float maximum,
                                   boolean includeMinimum) throws PCException {
        boolean flag;
        float value = 0;
        do {
            flag = false;
            try {
                System.out.print(prompt);
                try {
                    value = Float.parseFloat(readLine());
                } catch (NumberFormatException e) {
                    throw PCException.numberRequired(e);
                }
                if (!Float.isFinite(value) || (includeMinimum ? value < minimum : value <= minimum)
                        || value > maximum) {
                    throw PCException.valueOutOfRange(minimum, maximum, includeMinimum);
                }
            } catch (PCException e) {
                flag = e.isRecoverable();
                if (!e.isRecoverable()) {
                    throw e;
                }
                e.prelucrare();
            }
        } while (flag);
        return value;
    }


    // Проверяет цену в цикле и повторяет запрос после ошибки.
    private double readCheckedPrice(String prompt) throws PCException {
        boolean flag;
        double value = 0;
        do {
            flag = false;
            try {
                System.out.print(prompt);
                try {
                    value = Double.parseDouble(readLine());
                } catch (NumberFormatException e) {
                    throw new PCException("Цена должна быть числом.", e);
                }
                if (!Double.isFinite(value) || value < 0) {
                    throw new PCException("Цена должна быть конечным неотрицательным числом.");
                }
            } catch (PCException e) {
                flag = e.isRecoverable();
                if (!e.isRecoverable()) {
                    throw e;
                }
                e.prelucrare();
            }
        } while (flag);
        return value;
    }

    // Читает одну строку; ошибки потока и завершение ввода передаёт как PCException.
    private static String readLine() throws PCException {
        try {
            String value = KEYBOARD.readLine();
            if (value == null) {
                throw new PCException("Ввод завершён.", false);
            }
            return value;
        } catch (IOException e) {
            throw new PCException("Не удалось прочитать ввод: " + e.getMessage(), e, false);
        }
    }
}
