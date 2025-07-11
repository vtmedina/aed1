bool areOccurrencesEqual(char * s){
    int freq[26] = {0};
    char* ptr = s;
    while (*ptr) freq[*ptr++ - 'a']++;
    
    int val = freq[s[0] - 'a'];
    for (int i = 0; i < 26; i++)
        if (freq[i] && freq[i] != val) return false; 
    
    return true;
}
