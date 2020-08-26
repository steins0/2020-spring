/**
 * 设定一个向量类，后面保存结果只保存行号
 * */
public class Lvector {
    private int lineNum;
    private double[] v;

    public Lvector(int vsize){
        v = new double[vsize];
    }

    public Lvector() {
    }

    public Lvector(int lineNum, double[] v) {
        this.lineNum = lineNum;
        this.v = v;
    }

    public int getLineNum() {
        return lineNum;
    }

    public void setLineNum(int lineNum) {
        this.lineNum = lineNum;
    }

    public double[] getV() {
        return v;
    }

    public void setV(double[] v) {
        this.v = v;
    }
}
