import java.math.BigDecimal;
import java.util.HashMap;
import java.util.Map;

public class ArithmeticEncode {
    Map<Character,Section> CharacterSectionMap;//字符-区间对
    Map<Character,Integer> CharacterIntegerMap;//字符-数量区间对
    private char[] charSet;//字符集
    private Section endSection;//最后一个字符所在的区间
    private int sum;//字符总个数，初始情况等于字符集的个数
    private String to_encode;

    public ArithmeticEncode(String code, String to_encode){
        this.to_encode = to_encode;
        this.charSet = code.toCharArray();
        CharacterSectionMap = new HashMap<>();
        CharacterIntegerMap = new HashMap<>();
        endSection=new Section();
        sum=charSet.length;
        double length=1.0/charSet.length;
        BigDecimal templow=new BigDecimal(0);
        BigDecimal temphigh=new BigDecimal(0+length);
        for(int i=0;i<charSet.length;i++){
            Section section = new Section(templow, temphigh);
            CharacterSectionMap.put(charSet[i], section);
            CharacterIntegerMap.put(charSet[i], 1);
            templow = temphigh;
            temphigh = templow.add(BigDecimal.valueOf(length));
        }
        /*System.out.println("显示各个字符的区间：");
        for (int i=0;i<charSet.length;i++){
            System.out.println(CharacterSectionMap.get(charSet[i]).getLow()+"-"+CharacterSectionMap.get(charSet[i]).getHigh());
        }*/
        encode(to_encode);
    }

    public void updateforencode(char ch){//根据读入的字符，更新编码所需要的信息
        CharacterIntegerMap.put(ch, CharacterIntegerMap.get(ch)+1);
        sum+=1;
        BigDecimal temp_low=CharacterSectionMap.get(ch).getLow();
        BigDecimal temp_high=temp_low;
        //当前所有字符所在区间总长度
        BigDecimal length=CharacterSectionMap.get(ch).getHigh().add(CharacterSectionMap.get(ch).getLow().negate());
        BigDecimal temp_length;
        for(int i=0;i<charSet.length;i++){
            //区间长度等于字符概率乘区间总长度
            temp_length= length.multiply(new BigDecimal(CharacterIntegerMap.get(charSet[i])*1.0/sum));
            temp_high=temp_low.add(temp_length);
            CharacterSectionMap.get(charSet[i]).setLow(temp_low);
            CharacterSectionMap.get(charSet[i]).setHigh(temp_high);
            if(charSet[i]==ch){//用输入的当前字符来更新"最后一个区间（结果区间）"
                endSection.setLow(temp_low);
                endSection.setHigh(temp_high);
            }
            temp_low=temp_high;
        }
    }

    private BigDecimal binaryStringToBigDecimal(String binaryString) {
        int dotIndex = binaryString.indexOf('.');
        String decimalPart = binaryString.substring(dotIndex + 1);
        BigDecimal result = new BigDecimal("0");
        if ("".equals(decimalPart)) {
            return result;
        }
        for(int i = 0; i < decimalPart.length(); i++) {
            BigDecimal temp = new BigDecimal(decimalPart.substring(i, i + 1)).multiply(new BigDecimal(1).divide(new BigDecimal(2).pow(i + 1)));
            result = result.add(temp);
        }
        return result;
    }

    private String generateCodeword(Section section) {
        StringBuilder codeword = new StringBuilder("0.");
        while (binaryStringToBigDecimal(codeword.toString()).compareTo(section.getLow()) < 0) {
            codeword.append('1');
            if (binaryStringToBigDecimal(codeword.toString()).compareTo(section.getHigh()) > 0) {
                codeword.setCharAt(codeword.length() - 1, '0');
            }
        }
        return codeword.toString();
    }

    public void encode(String str){
        System.out.println("开始编码:");
        char[] chars_str=str.toCharArray();
        for (int i=0;i<chars_str.length;i++){
            updateforencode(chars_str[i]);
        }
        //System.out.println("最终区间："+endSection.getLow().doubleValue()+"-----"+endSection.getHigh().doubleValue());
        String result = generateCodeword(endSection);
        System.out.println("编码结果："+result);
        decode(result, str.length());
    }

    public void decode(String encode_result,int code_length){//根据01序列来解码,限定码长
        System.out.println("解码:");
        //初始化
        sum=charSet.length;
        endSection.setLow(new BigDecimal(0));
        endSection.setHigh(new BigDecimal(1));
        double length=1.0/charSet.length;
        BigDecimal templow=new BigDecimal(0);
        BigDecimal temphigh=new BigDecimal(0+length);
        for(int i=0;i<charSet.length;i++){
            Section section = new Section(templow, temphigh);
            CharacterSectionMap.put(charSet[i], section);
            CharacterIntegerMap.put(charSet[i], 1);
            templow = temphigh;
            temphigh = templow.add(BigDecimal.valueOf(length));
        }


        int i,j;
        BigDecimal codeword = binaryStringToBigDecimal(encode_result);
        //System.out.println("codeword="+codeword);
        String decode_result = "";
        for(i=0;i<code_length;i++){
            for(j=0;j<charSet.length;j++){
                if(codeword.compareTo(CharacterSectionMap.get(charSet[j]).getLow())>0
                        && codeword.compareTo(CharacterSectionMap.get(charSet[j]).getHigh())<0){
                    decode_result+=charSet[j];
                    updateforencode(charSet[j]);
                    break;
                }
            }
        }
        System.out.println("解码结果 "+decode_result);
        System.out.println("字符序列 "+to_encode);
    }
}
