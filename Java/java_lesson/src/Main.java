import java.util.Arrays;

// Главный класс с методом main, чтобы IDE не ругалась на неиспользуемый код
public class Main {
    public static void main(String[] args) {
        // Проверка работы всех конструкторов и методов
        Student student1 = new Student();
        student1.printInfo();

        System.out.println("----------------");

        Student student2 = new Student(0.2f, (byte) 110);
        student2.printInfo();

        System.out.println("----------------");

        Student student3 = new Student(student2);
        student3.printInfo();
    }
}

// Класс Student без модификатора public, чтобы его можно было держать в одном файле
class Student {
    String nickName;
    float laziness;     // 0..1 - лень
    byte IQ;           // 80…127
    int exams;
    int[] marks;       // динамический массив

    // 1. Конструктор по умолчанию
    public Student() {
        nickName = "oleg";
        laziness = (float) 0.5;    // 0.5f
        IQ = (byte) 127;
        exams = 6;
        marks = new int[exams];
        for (int i = 0; i < exams; i++) {
            marks[i] = 7;
        }
    }

    // 2. Конструктор с параметрами
    public Student(float laziness, byte IQ) {
        nickName = "artem";
        this.laziness = laziness;
        this.IQ = IQ;
        exams = 18;
        marks = new int[exams];
        for (int i = 0; i < exams; i++) {
            marks[i] = 8;
        }
    }

    // 3. Конструктор копирования
    public Student(Student prototype) {
        nickName = prototype.nickName;
        laziness = prototype.laziness;
        IQ = prototype.IQ;
        exams = prototype.exams;
        marks = new int[exams];
        for (int i = 0; i < exams; i++) {
            marks[i] = prototype.marks[i];
        }
    }

    // Метод вывода информации
    public void printInfo() {
        System.out.println("Student’s nick: " + nickName);
        System.out.println("Laziness: " + laziness);
        System.out.println("IQ: " + IQ);
        System.out.println("Exams: " + exams);
        System.out.print("Marks: ");
        for (int i = 0; i < exams; i++) {
            System.out.print(marks[i] + " ");
        }
        System.out.println();
    }
}

