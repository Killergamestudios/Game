import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.Files;
import java.util.*;


public class Build {
    List<String> allLines;
    ArrayList<Code> srcFiles = new ArrayList<>();

    public void listFilesForFolder(final File folder, String dir) {
        for (final File fileEntry : folder.listFiles()) {
            if (fileEntry.isDirectory()) {
                listFilesForFolder(fileEntry, (dir + fileEntry.getName() + "\\"));
            } else {
                String[] sp = fileEntry.getName().split("\\.");
                if(sp[sp.length-1].equals("cpp"))
                    srcFiles.add(new SourceCode(fileEntry.getName(), dir));
                else if(sp[sp.length-1].equals("h")) {
                    srcFiles.add(new HeaderCode(fileEntry.getName(), dir));
                }    
            }
        }
    }

    public void appendFiles() {

        try(FileWriter fw = new FileWriter("output.txt", true);
        BufferedWriter bw = new BufferedWriter(fw);
        PrintWriter out = new PrintWriter(bw))
        {
            for (String al : allLines) 
            {
                out.println(al);
                if(al.equals("  </ItemGroup>")) {
                    break;        
                }
            }
            out.println("  <ItemGroup>");
            for(Code sc : srcFiles) {
                if(sc instanceof SourceCode) {
                    break;
                }
                out.println("    <ClInclude Include=\"" + sc.getName() + "\">");
                out.println("      <Filter>" + sc.getDir().substring(0,sc.getDir().length()-1) + "</Filter>");
                out.println("    </ClInclude>");
            }
            out.println("  </ItemGroup>");
            out.println("  <ItemGroup>");
            for(Code hc : srcFiles) {
                if(hc instanceof HeaderCode) {
                    continue;
                }
                out.println("    <ClCompile Include=\"" + hc.getName() + "\">");
                out.println("      <Filter>" + hc.getDir().substring(0,hc.getDir().length()-1) + "</Filter>");
                out.println("    </ClCompile>");
            }
            out.println("  </ItemGroup>");
            out.println("</Project>");
        } catch (IOException e) {
            System.out.println("error");
        }
    }

    public void readOptions () {
        String fileName = "GameApp.vcxproj.filters";
        Path path = Paths.get(fileName);
        try {
            allLines = Files.readAllLines(path);
        } catch(IOException e) {
            System.out.println("error");
        }
    }
    
    public static void main(String[] args) {
        final File folder = new File("src");
        Build b = new Build();
        b.readOptions();
        b.listFilesForFolder(folder, "");
        b.appendFiles();
    }
}
class Code {
    String name;
    String dir;
    Code(String name, String dir) {
        super();
        this.name = name;
        this.dir = dir;
    }

    public String getDir() {
        return dir;
    }

    public String getName() {
        return name;
    }
}

class SourceCode extends Code{
    SourceCode(String name, String dir) {
        super(name,dir);
    }
}

class HeaderCode extends Code{
    HeaderCode(String name, String dir) {
        super(name,dir);
    }
}