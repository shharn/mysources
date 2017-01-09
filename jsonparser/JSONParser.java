import java.io.*;
import java.util.StringTokenizer;
import java.util.regex.Pattern;

/**
 * Created by shharn2 on 2017-01-09.
 */
public class JSONParser {
    private char currCh;
    private FileInputStream is;
    private String filePath;
    private JSONObject obj;
    JSONParser(String filePath) {
        currCh = 0;
        is = null;
        obj = null;
        this.filePath = filePath;
    }

    void nextChar() {
        try {
            currCh = (char) is.read();
        } catch(IOException ioe) {
            ioe.printStackTrace();
        }
    }

    void skipThisPattern(String regex) {
        while(Pattern.matches(regex, String.valueOf(currCh))) {
            nextChar();
        }
    }

    String getKey() throws InvalidJSONFormatException {
        skipThisPattern("\\s");
        assert(currCh == '"');

        String key = getString();

        nextChar();
        skipThisPattern("\\s");
        assert(currCh == ':');

        nextChar();
        return key;
    }

    String getString() throws InvalidJSONFormatException {
        String key = "";
        nextChar();
        while(!Pattern.matches("\"", String.valueOf(currCh))) {
            key += currCh;
            nextChar();
        }
        assert(currCh == '"');
        if(currCh != '"') {
            throw new InvalidJSONFormatException("Invalid JSON Format - " + currCh + " must be \"");
        }
        return key;
    }

    JSONInteger getInteger() throws InvalidJSONFormatException {
        String value = "";
        while(!Pattern.matches("[,\\s]", String.valueOf(currCh))) {
            if(!Pattern.matches("\\d", String.valueOf(currCh))) {
                throw new InvalidJSONFormatException("Invalid JSON Format - must be Integer");
            }
            value += currCh;
            nextChar();
        }
        return new JSONInteger(Integer.valueOf(value));
    }

    JSONList getList() throws InvalidJSONFormatException {
        nextChar();
        JSONList list = new JSONList();
        String listInString = "";
        while(!Pattern.matches("]", String.valueOf(currCh))) {
            listInString += currCh;
            nextChar();
        }

        StringTokenizer tokenizer = new StringTokenizer(listInString, ",");
        while(tokenizer.hasMoreTokens()) {
            String token = tokenizer.nextToken();
            if(token.charAt(0) == '"') { // String value
                JSONString stringValue = new JSONString(getString());
                list.getList().add(stringValue);
            } else if(Pattern.matches("\\d", String.valueOf(token.charAt(0)))) { // Integer value
                JSONInteger integerValue = getInteger();
                list.getList().add(integerValue);
            } else if(token.charAt(0) == '{') { // Object value
                JSONObject objectValue = getObject();
                list.getList().add(objectValue);
            } else {
                throw new InvalidJSONFormatException("Invalid JSON Format - currCh is " + currCh);
            }
        }
        return list;
    }

    JSONObject getObject() throws InvalidJSONFormatException {
        nextChar();
        skipThisPattern("\\s");
        JSONObject obj = new JSONObject();
        while(currCh != '}') {
            String key = getKey();
            skipThisPattern("\\s");
            JSONObject value = getValue();

            obj.getContainer().put(key, value);
        }
        skipThisPattern("\\s");
        assert(currCh == '}');
        if(currCh != '}') {
            throw new InvalidJSONFormatException("Invalid JSON Format - " + currCh +
                    " must be }");
        }
        return obj;
    }

    JSONObject getValue() throws InvalidJSONFormatException {
        JSONObject object = null;
        skipThisPattern("\\s");
        if(currCh == '"') { // String value
            object = new JSONString(getString());
        } else if (currCh == '[') { // List value
            object = getList();
        } else if (currCh == '{') { // Object value
            object = getObject();
        } else if(Pattern.matches("\\d", String.valueOf(currCh))) { // Integer value
            object = getInteger();
        } else {
            throw new InvalidJSONFormatException("Invalid JSON Format");
        }

        ////////////////////////////////////////////////
        // here, check if next non-whitespace character is ',' | '}' //
        ////////////////////////////////////////////////
        //               start here !!                //
        ////////////////////////////////////////////////
        skipThisPattern("\\s");
        if(currCh == ',') {

        } else if(currCh == '}')

        return object;
    }

    JSONObject parse() {
        try {
            is = new FileInputStream(filePath);
            nextChar();
            skipThisPattern("\\s");
            assert(currCh == '{');
            try {
                if (currCh != '{') {
                    throw new InvalidJSONFormatException("First Token must be left curly brace");
                }
                do {
                    obj = getObject();
                    nextChar();
                } while (currCh != '}');
                assert (currCh == '}');
                if (currCh != '}') {
                    throw new InvalidJSONFormatException("Last Token must be right curly brace");
                }
            } catch(InvalidJSONFormatException e) {
                e.print();
                System.exit(1);
            }
        } catch(FileNotFoundException e) {
            System.out.println("File Not Found");
            System.exit(1);
        } finally {
            try {
                is.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return obj;
    }
}
