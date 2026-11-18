import java.util.ArrayList;
import java.util.Random;

// Вспомогательные операции для создания, вывода и обработки компьютеров.
public final class PCFunctions {
    // Запрещает создавать экземпляры класса со статическими методами.
    private PCFunctions() {
    }

    // Печатает характеристики компьютера, его детали и сводные значения.
    public static void printInfo(PC pc) {
        System.out.println("==============================================");
        System.out.println("Владелец ПК:        " + pc.getNickName());
        System.out.println("Количество деталей: " + pc.getComponents().size());
        System.out.println("--- Список деталей ---");
        int[] index = {1};
        pc.getComponents().forEach(component -> {
            System.out.print("  [" + index[0]++ + "] ");
            component.printInfo();
        });
        System.out.println("Общий вес: " + getTotalWeight(pc) + " кг");
        System.out.println("Общая стоимость: " + getTotalPrice(pc) + " $");
        System.out.println("Средний год выпуска: " + getAverageReleaseYear(pc));
        System.out.println("==============================================");
    }

    // Суммирует цены всех деталей компьютера.
    public static double getTotalPrice(PC pc) {
        double total = 0;
        for (PCPart component : pc.getComponents()) {
            total += component.getPartPrice();
        }
        return total;
    }

    // Суммирует вес всех деталей компьютера.
    public static float getTotalWeight(PC pc) {
        float[] total = {0};
        pc.getComponents().forEach(component -> total[0] += component.getPartWeight());
        return total[0];
    }

    // Вычисляет средний год выпуска деталей; для пустого списка возвращает 0.
    public static float getAverageReleaseYear(PC pc) {
        if (pc.getComponents().isEmpty()) {
            return 0;
        }
        float[] sumYears = {0};
        pc.getComponents().forEach(component -> sumYears[0] += component.getReleaseYear());
        return sumYears[0] / pc.getComponents().size();
    }

    // Запрашивает данные компьютера и каждой его детали с проверкой ввода.
    public static void readFromKeyboardPC(PC pc) {
        try {
            pc.readFromKeyboardPC();
        } catch (PCException e) {
            e.prelucrare();
        }
    }

    // Добавляет новую комплектующую в список компьютера.
    public static void addNewComponents(PC pc, String name, float weight, float year, double price) {
        pc.getComponents().add(new PCPart(name, weight, year, price));
        System.out.println("Деталь \"" + name + "\" добавлена.");
    }

    // Заполняет компьютер случайным владельцем и случайными комплектующими.
    public static void fillRandom(PC pc) {
        Random rand = new Random();
        String[] names = {"Алексей", "Дмитрий", "Елена", "Мария", "Сергей", "Иван"};
        String[] sampleParts = {
                "CPU Intel", "GPU NVIDIA", "RAM Kingston",
                "SSD Samsung", "Motherboard ASUS", "PSU Corsair"
        };

        pc.setNickName(names[rand.nextInt(names.length)]);
        ArrayList<PCPart> components = new ArrayList<>();
        int componentCount = 3 + rand.nextInt(4);
        for (int i = 0; i < componentCount; i++) {
            components.add(new PCPart(
                    sampleParts[rand.nextInt(sampleParts.length)] + " v" + (i + 1),
                    0.2f + rand.nextFloat() * 2.5f,
                    2015f + rand.nextFloat() * (ErrorHandler.getMaximumYear() - 2015),
                    50.0 + rand.nextDouble() * 450.0
            ));
        }
        pc.setComponents(components);
    }

    // Находит компьютер с более старыми деталями и обновляет их год и цену.
    public static void compareAndUpgradeRelevance(PC pc, PC other) {
        float avg1 = getAverageReleaseYear(pc);
        float avg2 = getAverageReleaseYear(other);

        if (avg1 == avg2) {
            System.out.println("Компьютеры одинаковой актуальности.");
            return;
        }

        PC oldest = avg1 < avg2 ? pc : other;
        System.out.println("\nДо апгрейда:");
        printInfo(oldest);

        oldest.getComponents().forEach(component -> {
            component.setReleaseYear(ErrorHandler.getMaximumYear());
            component.setPartPrice(component.getPartPrice() + 100.0);
        });

        System.out.println("\nПосле апгрейда:");
        printInfo(oldest);
    }

    // Сравнивает суммарный вес двух компьютеров и выводит результат.
    public static void compareWeight(PC c1, PC c2) {
        float w1 = getTotalWeight(c1);
        float w2 = getTotalWeight(c2);

        System.out.println("\n=== Сравнение по весу ===");
        System.out.printf("ПК (%s): %.2f кг | ПК (%s): %.2f кг\n",
                c1.getNickName(), w1, c2.getNickName(), w2);

        if (w1 > w2) {
            System.out.printf("Компьютер %s тяжелее компьютера %s на %.2f кг.\n",
                    c1.getNickName(), c2.getNickName(), w1 - w2);
        } else if (w2 > w1) {
            System.out.printf("Компьютер %s тяжелее компьютера %s на %.2f кг.\n",
                    c2.getNickName(), c1.getNickName(), w2 - w1);
        } else {
            System.out.println("Оба компьютера имеют одинаковый вес.");
        }
    }

    // Подготавливает данные компьютера и передаёт их обработчику записи в файл.
    public static void saveToFile(PC pc, String filename) {
        ArrayList<String> lines = new ArrayList<>();
        lines.add(pc.getNickName());
        lines.add(Integer.toString(pc.getComponents().size()));
        for (PCPart component : pc.getComponents()) {
            lines.add(component.getNameModel());
            lines.add(Float.toString(component.getPartWeight()));
            lines.add(Float.toString(component.getReleaseYear()));
            lines.add(Double.toString(component.getPartPrice()));
        }

        ErrorHandler.writeLines(filename, lines);
    }
}
