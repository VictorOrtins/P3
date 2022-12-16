public class Caesar {
    public static final char[] ALPHA = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    public static final int ALPHA_SIZE = ALPHA.length;

    public Caesar(){

    }

    public String encryptString(String string){
        int stringSize = string.length();

        char[] ret = new char[stringSize];
        char[] stringArray = string.toUpperCase().toCharArray();

        for(int i = 0; i < stringSize; i++){
            try{
                int alphaIndex = returnAlphaIndex(stringArray[i]);
                ret[i] = ALPHA[(alphaIndex + 3) % 26];
            }
            catch(ArrayIndexOutOfBoundsException e){
                ret[i] = stringArray[i];
            }

        }

        return String.valueOf(ret);

    }

    public String decryptString(String string){
        int stringSize = string.length();

        char[] ret = new char[stringSize];
        char[] stringArray = string.toUpperCase().toCharArray();

        for (int i = 0; i < stringSize; i++){
            try{
                int alphaIndex = returnAlphaIndex(stringArray[i]);
                ret[i] = ALPHA[(alphaIndex + 23) % 26];
            }
            catch(ArrayIndexOutOfBoundsException e){
                ret[i] = stringArray[i];
            }
        }



        return String.valueOf(ret);
    }

    public int returnAlphaIndex(char character){
        for (int i = 0; i < ALPHA_SIZE; i++){
            if (character == ALPHA[i]){
                System.out.println("Index: " + i);
                return i;
            }
        }

        throw new ArrayIndexOutOfBoundsException();
        
    }
}
