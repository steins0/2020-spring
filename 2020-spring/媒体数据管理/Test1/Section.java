import java.math.BigDecimal;

/**
 * 2020-3-11 区间，用来表示每一个符号所在的区间
 * */
public class Section {
    private BigDecimal low;
    private BigDecimal high;

    public BigDecimal getLow() {
        return low;
    }

    public void setLow(BigDecimal low) {
        this.low = low;
    }

    public BigDecimal getHigh() {
        return high;
    }

    public void setHigh(BigDecimal high) {
        this.high = high;
    }

    public Section() {
    }

    public Section(BigDecimal low, BigDecimal high) {
        this.low = low;
        this.high = high;
    }
}
