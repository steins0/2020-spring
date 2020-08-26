import java.io.*;
import java.text.SimpleDateFormat;
import java.util.*;

/**
 * 暴力求解前1000个点的最近邻
 * */
public class Baoli {
    public static void main(String[] args) {
        SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");//设置日期格式
        System.out.println("开始搜索 "+df.format(new Date()));
        try {
            File file = new File("C:\\Users\\雷\\OneDrive\\xidian\\2020-spring\\媒体数据管理\\第三次实验\\ColorHistogram.asc");
            BufferedReader br = null;
            br = new BufferedReader(new FileReader(file));
            String str;
            List<Lvector> list = new ArrayList<>();
            int line = 1;
            while ((str=br.readLine())!=null){
                String[] arr = str.split(" ");
                double[] darr = new double[arr.length-1];
                for(int i=1;i<arr.length;i++){
                    darr[i-1]=Double.parseDouble(arr[i]);
                }
                Lvector lvector = new Lvector(line, darr);
                list.add(lvector);
                line++;
            }
            br.close();
            //暴力求解
            File resultf = new File("C:\\Users\\雷\\OneDrive\\xidian\\2020-spring\\媒体数据管理\\第三次实验\\check.txt");
            BufferedWriter bw = new BufferedWriter(new FileWriter(resultf));
            for(int i=0;i<1000;i++){
                List<Lvector> neighborscheck = new ArrayList<>(list);
                double[] v = list.get(i).getV();
                Collections.sort(neighborscheck, new Comparator<Lvector>() {
                    @Override
                    public int compare(Lvector v1, Lvector v2) {
                        Double d1 = LSH.cosDistance(v, v1.getV());
                        Double d2 = LSH.cosDistance(v, v2.getV());
                        return d1.compareTo(d2);
                    }
                });
                bw.write((i+1)+"\n");
                for(int j=1; j<=10; j++){
                    bw.write(j + " " +LSH.cosDistance(v, neighborscheck.get(j).getV()) + " "+neighborscheck.get(j).getLineNum());
                    //System.out.println(j+" "+neighborscheck.get(j).getLineNum());
                    bw.write('\n');
                }
                //bw.write("\n\n\n\n\n");
                bw.flush();
            }
            bw.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
        System.out.println("结束搜索 "+df.format(new Date()));
    }
}
