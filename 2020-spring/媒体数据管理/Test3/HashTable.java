import java.util.HashMap;

public class HashTable {
    private HashMap<Integer,Bucket> buckets;

    private int hashSize = 0;//hash函数的个数

    public HashTable(int hashSize) {
        this.buckets = new HashMap<Integer, Bucket>();
        this.hashSize = hashSize;
    }

    public void add(Lvector v, int seed){
        int key = LSH.combineHashes(hashSize, v.getV(),seed);
        //System.out.print("key="+key+" ");
        if(buckets.containsKey(key)){
            buckets.get(key).add(v);
        }else{
            Bucket bucket = new Bucket();
            bucket.add(v);
            buckets.put(key, bucket);
        }
    }

    public Bucket query(double[] v){
        int key = LSH.combineHashes(hashSize, v, 0);
        if(buckets.containsKey(key)){
            return buckets.get(key);
        }else{
            return null;
        }
    }

    public HashMap<Integer, Bucket> getBuckets() {
        return buckets;
    }
}
