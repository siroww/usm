import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Random;
import java.util.Scanner;

public class PC {
    // 1. Все поля делаем PRIVATE для защиты данных
    private String nickName;
    private Byte componentsCount;
    private String[] nameModel;
    private Float[] partWeights;
    private Float[] releaseYears;
    private Double[] partPrices;

    private static int createdCompsCount = 0;

    // 1. Конструктор по умолчанию
    public PC() {
        nickName = "NoName";
        componentsCount = 0;

        nameModel = new String[0];
        partWeights = new Float[0];
        releaseYears = new Float[0];
        partPrices = new Double[0];

        createdCompsCount++; // ИСПРАВЛЕНО: было componentsCount++
    }

    // 2. Конструктор с параметрами
    public PC(String nickName, Byte componentsCount, String[] nameModel, float[] partWeights,
              float[] releaseYears, double[] partPrices) {
        this.nickName = nickName;
        this.componentsCount = componentsCount;

        this.nameModel = new String[componentsCount];
        this.partWeights = new Float[componentsCount];
        this.releaseYears = new Float[componentsCount];
        this.partPrices = new Double[componentsCount];

        for (int i = 0; i < componentsCount; i++) {
            this.nameModel[i] = nameModel[i];
            this.partWeights[i] = partWeights[i];
            this.releaseYears[i] = releaseYears[i];
            this.partPrices[i] = partPrices[i];
        }

        createdCompsCount++;
    }

    // 3. Конструктор копирования
    public PC(PC prototype) {
        this.nickName = prototype.nickName;
        this.componentsCount = prototype.componentsCount;

        this.nameModel = new String[prototype.componentsCount];
        this.partWeights = new Float[prototype.componentsCount];
        this.releaseYears = new Float[prototype.componentsCount];
        this.partPrices = new Double[prototype.componentsCount];

        for (int i = 0; i < componentsCount; i++) {
            this.nameModel[i] = prototype.nameModel[i];
            this.partWeights[i] = prototype.partWeights[i];
            this.releaseYears[i] = prototype.releaseYears[i];
            this.partPrices[i] = prototype.partPrices[i];
        }

        createdCompsCount++;
    }

    // --- Методы set() и get() ---
    public String getNickName() { return nickName; }
    public void setNickName(String nickName) { this.nickName = nickName; }

    public byte getComponentsCount() { return componentsCount; }

    public String[] getNameModel() { return nameModel; }
    public void setNameModel(String[] nameModel) { this.nameModel = nameModel; }

    public Float[] getPartWeights() { return partWeights; }
    public void setPartWeights(Float[] partWeights) { this.partWeights = partWeights; }

    public Float[] getReleaseYears() { return releaseYears; }
    public void setReleaseYears(Float[] releaseYears) { this.releaseYears = releaseYears; }

    public Double[] getPartPrices() { return partPrices; }
    public void setPartPrices(Double[] partPrices) { this.partPrices = partPrices; }

    public static int getCreatedCompsCount() { return createdCompsCount; }

    // Печать всей технической информации
    public void printInfo() {
        System.out.println("==============================================");
        System.out.println("Владелец ПК:        " + nickName);
        System.out.println("Количество деталей: " + componentsCount);
        System.out.println("--- Список деталей ---");
        for (int i = 0; i < componentsCount; i++) {
            System.out.println("  [" + (i + 1) + "] " + nameModel[i] +
                    " | Вес: " + partWeights[i] + " кг" +
                    " | Год: " + releaseYears[i].intValue() +
                    " | Цена: " + partPrices[i] + " $");
        }
        System.out.println("Общий вес: " + getTotalWeight() + " кг");
        System.out.println("Общая стоимость: " + getTotalPrice() + " $");
        System.out.println("Средний год выпуска: " + getAverageReleaseYear());
        System.out.println("==============================================");
    }

    // Расчет общей стоимости
    public double getTotalPrice() {
        double total = 0;
        for (double price : partPrices) total += price;
        return total;
    }

    // Расчет общего веса
    public float getTotalWeight() {
        float total = 0;
        for (float weight : partWeights) total += weight;
        return total;
    }

    // Средний год выпуска
    public float getAverageReleaseYear() {
        if (componentsCount == 0) return 0;
        float sumYears = 0;
        for (float year : releaseYears) sumYears += year;
        return sumYears / componentsCount;
    }

    // Считывание с клавиатуры через Scanner
    public void readFromKeyboard() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Введите имя владельца: ");
        this.nickName = scanner.nextLine();

        System.out.print("Введите число деталей: ");
        this.componentsCount = scanner.nextByte();
        scanner.nextLine();

        this.nameModel = new String[this.componentsCount];
        this.partWeights = new Float[this.componentsCount];
        this.releaseYears = new Float[this.componentsCount];
        this.partPrices = new Double[this.componentsCount];

        for (int i = 0; i < this.componentsCount; i++) {
            System.out.println("--- Деталь " + (i + 1) + " ---");
            System.out.print(" Название: ");
            this.nameModel[i] = scanner.nextLine();
            System.out.print(" Вес (кг): ");
            this.partWeights[i] = scanner.nextFloat();
            System.out.print(" Год выпуска: ");
            this.releaseYears[i] = scanner.nextFloat();
            System.out.print(" Стоимость ($): ");
            this.partPrices[i] = scanner.nextDouble();
            scanner.nextLine();
        }
    }

    // Заполнение объекта случайными значениями
    public void fillRandom() {
        Random rand = new Random();
        String[] names = {"Алексей", "Дмитрий", "Елена", "Мария", "Сергей", "Иван"};
        String[] sampleParts = {"CPU Intel", "GPU NVIDIA", "RAM Kingston", "SSD Samsung", "Motherboard ASUS", "PSU Corsair"};

        this.nickName = names[rand.nextInt(names.length)];
        this.componentsCount = (byte) (3 + rand.nextInt(4));

        this.nameModel = new String[this.componentsCount];
        this.partWeights = new Float[this.componentsCount];
        this.releaseYears = new Float[this.componentsCount];
        this.partPrices = new Double[this.componentsCount];

        for (int i = 0; i < this.componentsCount; i++) {
            this.nameModel[i] = sampleParts[rand.nextInt(sampleParts.length)] + " v" + (i + 1);
            this.partWeights[i] = 0.2f + rand.nextFloat() * 2.5f;
            this.releaseYears[i] = 2015f + rand.nextFloat() * 11f; // ИСПРАВЛЕНО: совместимо со всеми версиями Java
            this.partPrices[i] = 50.0 + rand.nextDouble() * 450.0;
        }
    }

    // Сравнение 2-х компьютеров и апгрейд
    public void compareAndUpgradeRelevance(PC other) {
        float avg1 = this.getAverageReleaseYear();
        float avg2 = other.getAverageReleaseYear();

        if (avg1 == avg2) {
            System.out.println("Компьютеры одинаковой актуальности.");
            return;
        }

        PC oldest = (avg1 < avg2) ? this : other;

        System.out.println("\nДо апгрейда:");
        oldest.printInfo();

        for (int i = 0; i < oldest.componentsCount; i++) {
            oldest.releaseYears[i] = 2026f;
            oldest.partPrices[i] += 100.0;
        }

        System.out.println("\nПосле апгрейда:");
        oldest.printInfo();
    }

    // Сравнение 2-х компьютеров по весу
    public static void compareWeight(PC c1, PC c2) {
        float w1 = c1.getTotalWeight();
        float w2 = c2.getTotalWeight();

        System.out.println("\n=== Сравнение по весу ===");
        System.out.printf("ПК (%s): %.2f кг | ПК (%s): %.2f кг\n", c1.getNickName(), w1, c2.getNickName(), w2);

        if (w1 > w2) {
            System.out.printf("Компьютер %s тяжелее компьютера %s на %.2f кг.\n", c1.getNickName(), c2.getNickName(), (w1 - w2));
        } else if (w2 > w1) {
            System.out.printf("Компьютер %s тяжелее компьютера %s на %.2f кг.\n", c2.getNickName(), c1.getNickName(), (w2 - w1));
        } else {
            System.out.println("Оба компьютера имеют одинаковый вес.");
        }
    }

    // Сохранение в файл
    public void saveToFile(String filename) {
        try (PrintWriter writer = new PrintWriter(filename)) {
            writer.println(nickName);
            writer.println(componentsCount);

            for (int i = 0; i < componentsCount; i++) {
                writer.println(nameModel[i]);
                writer.println(partWeights[i]);
                writer.println(releaseYears[i]);
                writer.println(partPrices[i]);
            }
            System.out.println("Данные объекта успешно сохранены в файл: " + filename);
        } catch (FileNotFoundException e) {
            System.err.println("Ошибка при сохранении в файл " + filename + ": " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        PC c1 = new PC();
        c1.fillRandom();
        c1.printInfo();

        PC c2 = new PC("Иван", (byte) 2,
                new String[]{"SSD", "RAM"}, new float[]{0.1f, 0.05f}, new float[]{2019f, 2021f}, new double[]{80.0, 60.0});
        c2.printInfo();

        // Сеть компов
        PC[] network = new PC[]{c1, c2, new PC(c2)};

        System.out.println("\n--- Информация о сети ---");
        for (PC c : network) {
            c.printInfo();
        }

        PC.compareWeight(c1, c2);
        c1.compareAndUpgradeRelevance(c2);

        // Поиск самого дорогого
        PC expensive = network[0];
        for (PC c : network) {
            if (c.getTotalPrice() > expensive.getTotalPrice()) {
                expensive = c;
            }
        }
        System.out.println("\nСамый дорогой ПК принадлежит: " + expensive.getNickName() + " (" + expensive.getTotalPrice() + " $)");

        // Сохранение файла
        c2.saveToFile("comp_ivan.txt");

        System.out.println("\nЧисло созданных компов: " + PC.getCreatedCompsCount());
    }
}