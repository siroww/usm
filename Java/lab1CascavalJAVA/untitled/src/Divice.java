import java.io.*;
import java.util.Random;

public class Divice {
    public String name;
    private String id;
    private int weight;

    public Divice() {
        this.name = "noname";
        this.id = "unknown";
        this.weight = 0;
    }

    public Divice(String name, String id, int weights) {
        this.name = name;
        this.id = id;
        this.weight = weights;
    }

    public Divice(Divice prototype) {
        this.name = prototype.name;
        this.id = prototype.name;
        this.weight = prototype.weight;
    }

    public String getName() { return name; }
    void setName(String name) {this.name = name;}

    public String getId() { return id; }
    void setId( String id) { this.id = id}

    public int getWeights() { return weight}
    void setWeights(int weights) {this.weight = weights}

    public void print_info(){
        System.out.println("name model:" + name);
        System.out.println("id:" + id);
        System.out.println("weight:" + weight);
    }


}