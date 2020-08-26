import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.List;

/**
 * 衡量准确率
 * */
public class Check {
    public static void check(){
        List<Integer> Bresult = new ArrayList<>();//暴力求出的结果,只储存行号
        List<Integer> Lresult = new ArrayList<>();//LSH求出的结果
        try {
            File file = new File("C:\\Users\\雷\\OneDrive\\xidian\\2020-spring\\媒体数据管理\\第三次实验\\check.txt");
            File file1 = new File("E:\\cpp\\homewrok\\result3.txt");
            BufferedReader br = new BufferedReader(new FileReader(file));
            BufferedReader br1 = new BufferedReader(new FileReader(file1));
            String str,str1;
            int line,line1;
            while ((str=br.readLine())!=null && (str1=br1.readLine())!=null){
                String[] arr = str.split(" ");
                String[] arr1 = str1.split(" ");
                if(arr.length<3) continue;
                Bresult.add(Integer.parseInt(arr[2]));
                Lresult.add(Integer.parseInt(arr1[2]));
            }
            br.close();
        }catch (Exception e){
            e.printStackTrace();
        }
        int i,j,k;
        double p;
        double score = 0;
        for (i=0;i<1000;i++){
            p=0;
            for(j=0;j<10;j++){
                int line = Bresult.get(i*10+j);
                for(k=i*10;k<(i+1)*10;k++){
                    if(line==Lresult.get(k)){
                        p+=0.1;
                        break;
                    }
                }
            }
            score += p/1000.0;
            //System.out.println((i+1)+"  "+p);
        }
        System.out.println("score="+score);
    }
}
