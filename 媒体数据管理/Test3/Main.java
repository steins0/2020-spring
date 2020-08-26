import java.io.*;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        try {
            System.out.println("读取文件");
            File file = new File("C:\\Users\\雷\\OneDrive\\xidian\\2020-spring\\媒体数据管理\\第三次实验\\ColorHistogram.asc");
            BufferedReader br = new BufferedReader(new FileReader(file));
            String str;
            List<Lvector> list = new ArrayList<>();
            while ((str=br.readLine())!=null){
                int s = 0;
                String[] arr = str.split(" ");
                double[] darr = new double[arr.length-1];
                int line = Integer.parseInt(arr[0]);
                for(int i=1;i<arr.length;i++){
                    darr[i-1]=Double.parseDouble(arr[i]);
                }
                Lvector lvector = new Lvector(line, darr);
                list.add(lvector);
            }
            br.close();
            LSH lsh = new LSH(3, 7);
            //产生索引
            System.out.println("创建索引");
            int datalength = list.size();
            for(int i=0;i<datalength;i++){
                //System.out.println("i="+i);
                lsh.createIndex(list.get(i));
            }
            SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");//设置日期格式
            System.out.println("开始搜索 "+df.format(new Date()));
            File resultf = new File("E:\\cpp\\homewrok\\result3.txt");
            BufferedWriter bw = new BufferedWriter(new FileWriter(resultf));
            for(int t=0;t<1000;t++) {
                double[] v = list.get(t).getV();
                bw.write(list.get(t).getLineNum()+"\n");
                //bw.write("\n---------------------\n");
                List<Lvector> result = lsh.queryNeighbors(v, 10);
                if (result == null) {
                    System.out.println("未找到近邻！");
                } else {
                    for (int i = 0; i < result.size(); i++) {
                        Lvector a = result.get(i);
                        double distance = LSH.cosDistance(a.getV(), v);
                        bw.write((i+1)+" "+distance + " " + a.getLineNum());
                        bw.write('\n');
                    }
                }
                //bw.write("\n\n\n\n\n");
            }
            bw.close();
            System.out.println("结束搜索 "+df.format(new Date()));
        }catch (Exception e){
            e.printStackTrace();
        }
        Check.check();
    }
}
