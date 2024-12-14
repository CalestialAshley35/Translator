#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// Translation dictionaries
map<string, string> englishToSpanish = {
    {"hello", "hola"}, {"world", "mundo"}, {"eat", "comer"}, {"robot", "robot"},
    {"bot", "bot"}, {"ai", "inteligencia artificial"}, {"how", "cómo"},
    {"are", "estás"}, {"you", "tú"}, {"good", "bueno"}, {"morning", "mañana"},
    {"night", "noche"}, {"thank", "gracias"}, {"please", "por favor"},
    {"love", "amor"}, {"happy", "feliz"}, {"friend", "amigo"},
    {"how are you", "¿cómo estás?"}, {"good morning", "buenos días"},
    {"good night", "buenas noches"}, {"thank you", "gracias"},
    {"i love you", "te amo"}, {"goodbye", "adiós"},
    {"what's your name?", "¿cuál es tu nombre?"},
    {"my name is", "mi nombre es"}, {"see you later", "hasta luego"},
    {"please wait", "por favor espera"},
    {"i don't understand", "no entiendo"},
    {"where is the bathroom?", "¿dónde está el baño?"},
    {"how much does it cost?", "¿cuánto cuesta?"},
    {"sorry", "lo siento"}, {"excuse", "perdón"},
    {"good afternoon", "buenas tardes"}, {"good evening", "buenas noches"},
    {"how old are you?", "¿cuántos años tienes?"},
    {"i am fine", "estoy bien"}, {"what time is it?", "¿qué hora es?"},
    {"it's hot", "hace calor"}, {"it's cold", "hace frío"},
    {"can you help me?", "¿puedes ayudarme?"},
    {"i need help", "necesito ayuda"},
    {"where are you from?", "¿de dónde eres?"},
    {"i'm from", "soy de"}, {"what's the weather like?", "¿cómo está el clima?"},
    {"it's raining", "está lloviendo"}, {"it's sunny", "está soleado"},
    {"how do I get to?", "¿cómo llego a?"},
    {"what's your phone number?", "¿cuál es tu número de teléfono?"},
    {"i'm lost", "estoy perdido"},
    {"can I have the bill?", "¿puedo tener la cuenta?"},
    {"is this seat taken?", "¿está ocupado este asiento?"},
    {"i like it", "me gusta"}, {"i don't like it", "no me gusta"},
    {"how do you say in Spanish?", "¿cómo se dice en español?"},
    {"nice to meet you", "mucho gusto"}, {"yes", "sí"}, {"no", "no"},
    {"maybe", "tal vez"}, {"thank you very much", "muchas gracias"},
    {"you're welcome", "de nada"}, {"please repeat", "por favor repita"},
    {"i don't know", "no sé"}, {"i don't care", "no me importa"},
    {"do you speak English?", "¿hablas inglés?"},
    {"what is this?", "¿qué es esto?"},
    {"this is my friend", "este es mi amigo"},
    {"have a good day", "que tengas un buen día"},
    {"see you soon", "nos vemos pronto"}
};

map<string, string> englishToGreek = {
    {"hello", "γεια"}, {"world", "κόσμος"}, {"eat", "τρώω"},
    {"robot", "ρομπότ"}, {"how are you", "πώς είσαι;"},
    {"good morning", "καλημέρα"}, {"good night", "καληνύχτα"},
    {"thank you", "ευχαριστώ"}, {"i love you", "σ' αγαπώ"},
    {"goodbye", "αντίο"}, {"please", "παρακαλώ"},
    {"sorry", "συγνώμη"}, {"friend", "φίλος"},
    {"how", "πώς"}, {"are", "είσαι"}, {"you", "εσύ"},
    {"it's raining", "βρέχει"}, {"it's sunny", "είναι ηλιόλουστος"},
    {"where are you from?", "από πού είσαι;"}
};

map<string, string> englishToBengali = {
    {"hello", "হ্যালো"}, {"world", "পৃথিবী"}, {"eat", "খাওয়া"},
    {"robot", "রোবট"}, {"how are you", "আপনি কেমন আছেন?"},
    {"good morning", "সুপ্রভাত"}, {"good night", "শুভ রাত্রি"},
    {"thank you", "ধন্যবাদ"}, {"i love you", "আমি তোমাকে ভালবাসি"},
    {"goodbye", "বিদায়"}, {"please", "অনুগ্রহ করে"},
    {"sorry", "দুঃখিত"}, {"friend", "বন্ধু"},
    {"how", "কীভাবে"}, {"are", "হয়"}, {"you", "আপনি"},
    {"it's raining", "বৃষ্টি হচ্ছে"}, {"it's sunny", "রোদেলা"},
    {"where are you from?", "আপনি কোথা থেকে এসেছেন?"}
};

// Function to split input text into words
vector<string> splitWords(const string& text) {
    vector<string> words;
    stringstream ss(text);
    string word;
    while (ss >> word) {
        words.push_back(word);
    }
    return words;
}

// Function to translate text
string translateText(const string& inputText, const string& targetLanguage) {
    map<string, string>* dictionary;

    // Select translation dictionary
    if (targetLanguage == "spanish") {
        dictionary = &englishToSpanish;
    } else if (targetLanguage == "greek") {
        dictionary = &englishToGreek;
    } else if (targetLanguage == "bengali") {
        dictionary = &englishToBengali;
    } else {
        return "Unsupported language!";
    }

    vector<string> words = splitWords(inputText);
    string translatedText;
    for (size_t i = 0; i < words.size(); ++i) {
        // Check for phrases
        string currentWord = words[i];
        string nextWord = (i + 1 < words.size()) ? words[i + 1] : "";
        string phrase = currentWord + " " + nextWord;

        if (dictionary->count(phrase)) {
            translatedText += (*dictionary)[phrase] + " ";
            ++i; // Skip next word
        } else if (dictionary->count(currentWord)) {
            translatedText += (*dictionary)[currentWord] + " ";
        } else {
            translatedText += currentWord + " ";
        }
    }

    return translatedText;
}

int main() {
    string inputText, targetLanguage;

    // Get input from the user
    cout << "Enter the text to translate: ";
    getline(cin, inputText);

    cout << "Enter the target language (spanish/greek/bengali): ";
    cin >> targetLanguage;

    // Convert target language to lowercase
    transform(targetLanguage.begin(), targetLanguage.end(), targetLanguage.begin(), ::tolower);

    // Translate the text
    string result = translateText(inputText, targetLanguage);

    // Output the result
    cout << "Translated Text: " << result << endl;

    return 0;
}
