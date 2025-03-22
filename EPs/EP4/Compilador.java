package EPs.EP4;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class Compilador {
    public static void main(String[] args) {
        String caminhoArquivo ="C:\\Users\\phpmm\\Documents\\Puc\\GITHUB\\AC2\\testeula.ula";
        String caminhoSaida = "testeula.hex"; 


        String X = "";
        String Y = "";
        String W = "";

        try (BufferedReader br = new BufferedReader(new FileReader(caminhoArquivo));
            BufferedWriter bw = new BufferedWriter(new FileWriter(caminhoSaida))) {
            String linha;

            while ((linha = br.readLine()) != null) {
                if (linha.contains("fim.")) {
                    break;
                }
                
                linha = linha.replaceAll(";", "").trim();

                if (linha.startsWith("X")) {
                    String[] partes = linha.split("=");
                    if (partes.length > 1) {
                        X = partes[1].trim();
                    }
                }

                if (linha.startsWith("Y")) {
                    String[] partes = linha.split("=");
                    if (partes.length > 1) {
                        Y = partes[1].trim();
                    }
                }
                

                if (linha.startsWith("W")) {
                    String[] partes = linha.split("=");
                    if (partes.length > 1) {
                        W = partes[1].trim();
                        
                        if ("zeroL".equals(W)) {
                            W = "0";
                        } else if ("umL".equals(W)) {
                            W = "1";
                        } else if ("copiaA".equals(W)) {
                            W = "2";
                        } else if ("copiaB".equals(W)) {
                            W = "3";
                        } else if ("nA".equals(W)) {
                            W = "4";
                        } else if ("nB".equals(W)) {
                            W = "5";
                        } else if ("AenB".equals(W)) {
                            W = "6";
                        } else if ("nAeB".equals(W)) {
                            W = "7";
                        } else if ("AxB".equals(W)) {
                            W = "8";
                        } else if ("nAxnB".equals(W)) {
                            W = "9";
                        } else if ("nAxnBn".equals(W)) {
                            W = "A";
                        } else if ("AeB".equals(W)) {
                            W = "B";
                        } else if ("AeBn".equals(W)) {
                            W = "C";
                        } else if ("AoBn".equals(W)) {
                            W = "D";
                        } else if ("AoB".equals(W)) {
                            W = "E";
                        } else if ("nAonBn".equals(W)) {
                            W = "F";
                        }

                        if (!X.isEmpty() && X.matches("\\d+") && Integer.parseInt(X) >= 10) {
                            X = String.valueOf((char) ('A' + Integer.parseInt(X) - 10));
                        }
                        
                        if (!Y.isEmpty() && Y.matches("\\d+") && Integer.parseInt(Y) >= 10) {
                            Y = String.valueOf((char) ('A' + Integer.parseInt(Y) - 10));
                        }

                        String resultado = X + Y + W;
                        bw.write(resultado);
                        bw.newLine(); 
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
