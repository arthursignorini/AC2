import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class Compilador {
    public static void main(String[] args) {
        // Definição dos caminhos dos arquivos de entrada e saída
        String caminhoArquivo = "dados/testeula.ula";
        String caminhoSaida = "dados/testeula.hex";

        // Variáveis para armazenar os valores extraídos do arquivo
        String X = "";
        String Y = "";
        String W = "";

        // Bloco try-with-resources para garantir o fechamento correto dos arquivos
        try (BufferedReader br = new BufferedReader(new FileReader(caminhoArquivo));
             BufferedWriter bw = new BufferedWriter(new FileWriter(caminhoSaida))) {
            
            String linha;

            // Loop para ler cada linha do arquivo de entrada
            while ((linha = br.readLine()) != null) {
                // Se encontrar "fim.", interrompe a leitura
                if (linha.contains("fim.")) {
                    break;
                }

                // Ignora a linha que contém "inicio"
                if (!(linha.contains("inicio"))) {
                    // Remove os pontos e vírgulas da linha e remove espaços extras
                    linha = linha.replaceAll(";", "").trim();

                    // Se a linha começa com "A", extrai o valor e armazena em X
                    if (linha.startsWith("X")) {
                        String[] partes = linha.split("=");
                        if (partes.length > 1) {
                            X = partes[1].trim();
                        }
                    }

                    // Se a linha começa com "B", extrai o valor e armazena em Y
                    if (linha.startsWith("Y")) {
                        String[] partes = linha.split("=");
                        if (partes.length > 1) {
                            Y = partes[1].trim();
                        }
                    }

                    // Se a linha começa com "W", extrai o valor e armazena em W
                    if (linha.startsWith("W")) {
                        String[] partes = linha.split("=");
                        if (partes.length > 1) {
                            W = partes[1].trim();

                            // Conversão dos valores de W para código hexadecimal correspondente
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

                            // Conversão de valores decimais maiores que 9 em caracteres hexadecimais para X
                            if (!X.isEmpty() && X.matches("\\d+") && Integer.parseInt(X) >= 10) {
                                X = String.valueOf((char) ('A' + Integer.parseInt(X) - 10));
                            }

                            // Conversão de valores decimais maiores que 9 em caracteres hexadecimais para Y
                            if (!Y.isEmpty() && Y.matches("\\d+") && Integer.parseInt(Y) >= 10) {
                                Y = String.valueOf((char) ('A' + Integer.parseInt(Y) - 10));
                            }

                            // Concatenação dos valores X, Y e W para formar o código final
                            String resultado = X + Y + W;
                            
                            // Escrita do resultado no arquivo de saída
                            bw.write(resultado);
                            bw.newLine(); // Adiciona uma nova linha no arquivo
                        }
                    }
                }
            }
        } catch (IOException e) {
            // Tratamento de erro caso haja problemas na leitura ou escrita dos arquivos
            e.printStackTrace();
        }
    }
}
