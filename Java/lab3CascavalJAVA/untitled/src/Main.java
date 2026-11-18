import java.util.ArrayList;
import java.util.Arrays;

public class Main {
    // Создаёт примеры компьютеров, выводит их данные и находит компьютер с минимумом деталей.
    public static void main(String[] args) {
        PC c1 = new PC();
        PCFunctions.fillRandom(c1);
        PCFunctions.printInfo(c1);

        PC c2 = new PC(
                "Alex",
                new ArrayList<>(Arrays.asList(
                        new PCPart("CPU", 0.3f, 2020f, 150.0),
                        new PCPart("GPU", 0.8f, 2023f, 500.0)
                )),
                0,
                "NON-color",
                0,
                "NON-OC"
        );
        PCFunctions.printInfo(c2);

        // Список компьютеров сети хранится в ArrayList.
        ArrayList<PC> network = new ArrayList<>();
        network.add(c1);
        network.add(c2);
        network.add(new PC(c2));

        System.out.println("\n--- Информация о сети ---");
        network.forEach(PCFunctions::printInfo);





        // Обычный цикл for ищет компьютер с наименьшим количеством комплектующих.
        PC minComponents = network.get(0);
        for (PC pc : network) {
            if (pc.getComponents().size() < minComponents.getComponents().size()) {
                minComponents = pc;
            }
        }
        System.out.println("\nPC с наименьшим количеством компонентов: "
                + minComponents.getComponents().size());

        PC pc3 = new PC();
        try {
            pc3.readFromKeyboardPC();
        } catch (PCException e) {
            e.prelucrare();
        }
        for (int i =0; i < network.size(); i++) {
            PCFunctions.printInfo(network.get(i));
        }

    }
}
