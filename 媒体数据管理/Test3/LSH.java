import java.util.*;

public class LSH {
    //计算余弦距离
    public static double cosDistance(double[] v1,double[] v2){
        double distance = 0;
        distance = 1-dotProduct(v1, v2)/Math.sqrt(dotProduct(v1, v1)*dotProduct(v2, v2));
        return distance;
    }
    //求点积
    public static double dotProduct(double[] v1,double[] v2){
        int dimension = v1.length;
        double product = 0;
        for(int i=0; i<dimension; i++){
            product+=v1[i]*v2[i];
        }
        return product;
    }
    //随机投影生成hash值
    public static int generateHash(double[] v,int seed){
        int dimension = v.length;
        Random random = new Random(seed);

        //生成随机超平面
        double[] randHyperPlane = new double[dimension];
        for(int i=0; i<dimension; i++){
            randHyperPlane[i]=random.nextGaussian();
        }
        return dotProduct(v, randHyperPlane)>0?1:0;
    }
    //合并多个hash值，提高效率,相当于把向量看成了一个二进制数
    public static int combineHashes(int hashSize, double[] v,int seed){
        int[] hashes = new int[hashSize];

        for(int i=0;i<hashSize;i++){
            hashes[i]=generateHash(v,i*10+seed);
        }

        int combine = 0;
        int power = 1;
        for(int i=0;i<hashes.length;i++){
            combine+=hashes[i]==0?0:power;
            power*=2;
        }
        return combine%7;
    }
    //创建索引
    public void createIndex(Lvector v){
        int i = 0;
        for(HashTable table:tables){
            table.add(v,i);
            i++;
        }
    }
    //查询近似
    public List<Lvector> queryNeighbors(final double[] v,int count){
        Set<Lvector> neighborSet = new HashSet<>();
        for(HashTable table:tables){
            Bucket bucket = table.query(v);
            if(bucket==null){
                return null;
            }else{
                neighborSet.addAll(bucket.getData());
            }
        }
        //System.out.println("neighborSet.size()="+neighborSet.size());
        List<Lvector> neighbors = new ArrayList<Lvector>(neighborSet);
        Collections.sort(neighbors, new Comparator<Lvector>() {
            @Override
            public int compare(Lvector v1, Lvector v2) {
                Double d1 = cosDistance(v, v1.getV());
                Double d2 = cosDistance(v, v2.getV());
                return d1.compareTo(d2);
            }
        });
        if(neighbors.size()>count){
            neighbors=neighbors.subList(0, count);
        }
        return neighbors;
    }

    private int tableNum = 0;//哈希表个数
    private int hashNum = 0;//哈希函数个数

    private ArrayList<HashTable> tables;

    public LSH(int tableNum, int hashNum){
        this.tableNum = tableNum;
        this.hashNum = hashNum;
        this.tables = new ArrayList<HashTable>();
        for(int i=0;i<tableNum;i++){
            HashTable table = new HashTable(hashNum);
            tables.add(table);
        }
    }

    public int getTableNum() {
        return tableNum;
    }

    public int getHashNum() {
        return hashNum;
    }
}
