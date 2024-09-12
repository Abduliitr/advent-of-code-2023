import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

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
    ArrayList<String> giveninputs;
    Challenge(ArrayList<String> inputs){
        giveninputs = inputs;
    }

    @SuppressWarnings("unused")
    private void setup(){

    }

    public long solve(){
        return giveninputs
                .stream()
                .map(eachinput -> solveEach(eachinput))
                .reduce(0, (a, b) -> a + b);
    }

    private Integer solveEach(String input) {
        Set<Integer> winners = new HashSet<>();
        int i = 0, n = input.length();
        while(i < n && input.charAt(i) != ':') i++;

        i++;    // skip :
        String temp = "";
        while(i < n && input.charAt(i) != '|'){
            if(Utils.isdigit(input.charAt(i))){
                temp += input.charAt(i);
            }else{
                if(temp != "") winners.add(Integer.parseInt(temp));
                temp = "";
            }
            i++;
        }
        if(temp != "") winners.add(Integer.parseInt(temp));
        temp = "";

        i++;    // skip |
        int res = 0;
        while(i < n){
            if(Utils.isdigit(input.charAt(i))){
                temp += input.charAt(i);
            }else{
                if(temp != "" && winners.contains(Integer.parseInt(temp))){ 
                    if(res == 0) res = 1;
                    else res = res * 2;
                }
                temp = "";
            }
            i++;
        }

        if(temp != "" && winners.contains(Integer.parseInt(temp))){ 
            if(res == 0) res = 1;
            else res = res * 2;
        }

        return res;
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