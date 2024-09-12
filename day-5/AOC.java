import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

class Utils{
    public static boolean isdigit(char ch){
        return Character.isDigit(ch);
    }
}

class InputReader{
    public ArrayList<String> getReadInputs(String inputFile) throws FileNotFoundException{
        File file = new File(inputFile);
        Scanner sc = new Scanner(file);
        ArrayList<String> allinputs = new ArrayList<>();

        while(sc.hasNextLine()){
            allinputs.add(sc.nextLine());
        }
        sc.close();
        return allinputs;
    }
}

class Challenge{
    List<String> giveninputs;

    List<Long> seeds;

    Challenge(List<String> inputs){
        giveninputs = inputs;
        seeds = new ArrayList<>();
    }

    @SuppressWarnings("unused")
    private void setup(){

    }

    public long solve(){

        seeds = Arrays.asList(
                    Arrays.copyOfRange(
                        giveninputs.get(0).split(" "), 1, 
                        giveninputs.get(0).split(" ").length)
                ).stream().map(Long::parseLong).toList();
        
        /*
        List<Long> seedsV2 = Arrays.asList(
                    Arrays.copyOfRange(
                        giveninputs.get(0).split(" "), 1, 
                        giveninputs.get(0).split(" ").length)
                ).stream().map(Long::parseLong).toList();

        for(Long i = 0L; i < seedsV2.get(1); i++){
            seeds.add(seedsV2.get(0) + i);
        }
        for(Long i = 0L; i < seedsV2.get(3); i++){
            seeds.add(seedsV2.get(2) + i);
        }
        */

        System.out.println("Initial seeds... " + seeds);

        int i = 1;
        while(i < giveninputs.size()){
            // logic here.
            if(giveninputs.get(i) == ""){
                i++; continue;
            }

            // if mapping starts here.
            System.out.println("\nProcesssing.. " + giveninputs.get(i));
            i = processMappings(i);
            System.out.println("After processing seeds... " + seeds);
        }
        // return giveninputs
        //         .stream()
        //         .map(eachinput -> solveEach(eachinput))
        //         .reduce(0, (a, b) -> a + b);

        // process final seedings
        return Collections.min(seeds);
    }

    private int processMappings(int i) {
        List<String> postList = Arrays.asList(giveninputs.get(i).split(" "));
        // System.out.println("Debug " + postList);
        if(postList.size() != 2){
            // this is mapping indicator.
            return i + 1;
        }

        int count = i + 1;
        // store the mappings
        List<Long> arr = new ArrayList<>();
        Map<Long, Long> m = new HashMap<>();
        Long maxx = 0L;
        while(count < giveninputs.size() && giveninputs.get(count) != ""){
            String[] input = giveninputs.get(count).split(" ");
            Long destStart = Long.parseLong(input[0]);
            Long srcStart = Long.parseLong(input[1]);
            Long range = Long.parseLong(input[2]);

            m.put(srcStart, destStart);
            if(!m.containsKey(srcStart + range)){
                maxx = Long.max(maxx, srcStart + range);
                m.put(srcStart + range, srcStart + range);
            }

            arr.add(srcStart);
            count++;

            // System.out.println("Debug " + arr);
            // System.out.println(m);
            // for(String x: input) System.out.print(x);
            // System.out.println();
        }

        if(!m.containsKey(0L)){
            m.put(0L, 0L);
            arr.add(0L);
        }
        arr.add(maxx);

        Collections.sort(arr);

        System.out.println("Debug arr and map: " + arr);
        System.out.println(m);

        // need to find right mappings for the seeds;
        List<Long> temp = new ArrayList<>();
        for(int j = 0; j < seeds.size(); j++){
            Long old = seeds.get(j);
            Long mappingSrc = getMappingOfJustLessThanOrEqualTo(arr, seeds.get(j));
            Long updated = (m.get(mappingSrc) + (old - mappingSrc));
            // int updated = m.getOrDefault(getMappingOfJustLessThanOrEqualTo(arr, seeds.get(j)), old);

            temp.add(updated);

            // System.out.println("Debug " + seeds);
        }

        seeds = temp;
        return count;
    }

    Long getMappingOfJustLessThanOrEqualTo(List<Long> arr, Long val){
        int start = 0, end = arr.size() - 1;
        int res = -1;
        // System.out.println("Debug binary search" + arr + " " + val);
        // System.out.println(start + " " + end + " " + res);
        while(start <= end){
            int mid = (start + end)/2;
            if(arr.get(mid) <= val){
                res = mid;
                start = mid + 1;
            }else{
                end = mid - 1;
            }
        }

        // System.out.println("Debug binary search" + arr + " " + val + " " + res + " " + 
        //     (res != -1 ? arr.get(res) : val));

        return arr.get(res);
    }

    private int solveEach(String eachinput) {
        return -1;
    }

}

public class AOC{
    public static void main(String[] args) {
        
        InputReader inputReader = new InputReader();
        Challenge challenge;
        try {
            challenge = new Challenge(inputReader.getReadInputs(args[0]));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
            return;
        }

        long res = challenge.solve();
        System.out.println("Calculated result : " + res);
    }    
}