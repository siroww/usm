import java.time.Year;
import java.util.Random;

// Отдельная комплектующая компьютера с моделью, весом, годом выпуска и ценой.
public class PCPart {
    private String nameModel;
    private float partWeight;
    private float releaseYear;
    private double partPrice;

    // Создаёт деталь со случайными характеристиками из допустимых диапазонов.
    public PCPart() {
        Random random = new Random();
        String[] sampleParts = {
                "CPU Intel", "GPU NVIDIA", "RAM Kingston",
                "SSD Samsung", "Motherboard ASUS", "PSU Corsair"
        };
        this.nameModel = sampleParts[random.nextInt(sampleParts.length)];
        this.partWeight = 0.2f + random.nextFloat() * 2.5f;
        this.releaseYear = 2015f + random.nextFloat() * (Year.now().getValue() - 2015);
        this.partPrice = 50.0 + random.nextDouble() * 450.0;
    }

    // Создаёт деталь с характеристиками, переданными в параметрах.
    public PCPart(String nameModel, float partWeight, float releaseYear, double partPrice) {
        this.nameModel = nameModel;
        this.partWeight = partWeight;
        this.releaseYear = releaseYear;
        this.partPrice = partPrice;
    }

    // Создаёт копию другой комплектующей.
    public PCPart(PCPart prototype) {
        this(prototype.nameModel, prototype.partWeight, prototype.releaseYear, prototype.partPrice);
    }

    // Выводит все характеристики детали в консоль.
    public void printInfo() {
        System.out.println(nameModel
                + " | Вес: " + partWeight + " кг"
                + " | Год: " + (int) releaseYear
                + " | Цена: " + partPrice + " $");
    }

    // Возвращает и изменяет название модели детали.
    public String getNameModel() {
        return nameModel;
    }

    public void setNameModel(String nameModel) {
        this.nameModel = nameModel;
    }

    // Возвращает и изменяет вес детали.
    public float getPartWeight() {
        return partWeight;
    }

    public void setPartWeight(float partWeight) {
        this.partWeight = partWeight;
    }

    // Возвращает и изменяет год выпуска детали.
    public float getReleaseYear() {
        return releaseYear;
    }

    public void setReleaseYear(float releaseYear) {
        this.releaseYear = releaseYear;
    }

    // Возвращает и изменяет цену детали.
    public double getPartPrice() {
        return partPrice;
    }

    public void setPartPrice(double partPrice) {
        this.partPrice = partPrice;
    }
}
