#include <iostream>
#include <string>
#include <cstdlib> // Για τις συναρτήσεις rand() και srand()
#include <ctime>     // Για τη συνάρτηση time()
#include <algorithm> // Για τη συνάρτηση shuffle

using namespace std;

// Ορισμός της κλάσης Song
class Song {
public:
    string title;
    string singerName;
    string singerSurname;
    string albumTitle;
    int likes;
    Song* next;
    Song* prev;

    // Κατασκευαστής της κλάσης Song
    Song(const string& _title, const string& _singerName, const string& _singerSurname, const string& _albumTitle, int _likes) {
        title = _title;
        singerName = _singerName;
        singerSurname = _singerSurname;
        albumTitle = _albumTitle;
        likes = _likes;
    }

    // Μέθοδοι για την ανάγνωση και την εγγραφή των δεικτών next και prev
    Song* getNext() {
        return next;
    }

    Song* getPrev() {
        return prev;
    }

    void setNext(Song* n) {
        next = n;
    }

    void setPrev(Song* p) {
        prev = p;
    }

};

// Ορισμός της κλάσης Playlist
class Playlist {
private:
    string name;
    // Διπλά συνδεδεμένη λίστα τραγουδιών
    Song* head;
    Song* tail;

public:
    // Κατασκευαστής της κλάσης Playlist
    Playlist(const string& _name) : name(_name), head(nullptr), tail(nullptr) {}

    // Μέθοδος για την εισαγωγή νέου τραγουδιού στη λίστα
    void insertSong(const Song& newSong) {
        Song* newSongPtr = new Song(newSong); // Δημιουργία αντιγράφου του τραγουδιού
        if (head == nullptr) {
            head = newSongPtr;
            tail = newSongPtr;
        } else {
            tail->next = newSongPtr;
            newSongPtr->prev = tail;
            tail = newSongPtr;
        }
    }

    // Μέθοδος για την εκτύπωση της λίστας τραγουδιών
    void printPlaylist() const {
    Song* current = head;
    while (current != nullptr) {
        cout << "Title: " << current->title << endl;
        cout << "Singer: " << current->singerName << " " << current->singerSurname << endl;
        cout << "Album: " << current->albumTitle << endl;
        cout << "Likes: " << current->likes << endl;
        cout << "---------------------" << endl;
        current = current->next;
        if (current == nullptr) break; // Προσθέτουμε έναν έλεγχο για να αποφύγουμε το infinite loop
    }
}

    // Μέθοδος για την αναπαραγωγή του επόμενου τραγουδιού
    void nextSong() {
    if (head == nullptr) {
        cout << "Playlist is empty. Cannot play next song." << endl;
        return;
    }

    if (head->next != nullptr) {
        head = head->next;
        cout << "Playing next song..." << endl;
        cout << "---------------------" << endl;
        cout << "Title: " << head->title << endl;
        cout << "Singer: " << head->singerName << " " << head->singerSurname << endl;
        cout << "Album: " << head->albumTitle << endl;
        cout << "Likes: " << head->likes << endl;
        cout << "---------------------" << endl;
    } else {
        cout << "No next song available." << endl;
    }
}

    // Μέθοδος για την αναπαραγωγή του προηγούμενου τραγουδιού
    void prevSong() {
        if (head == nullptr) {
            cout << "Playlist is empty. Cannot play previous song." << endl;
            return;
        }

        if (head->prev != nullptr) {
            head = head->prev;
            cout << "Playing previous song..." << endl;
            cout << "---------------------" << endl;
            cout << "Title: " << head->title << endl;
            cout << "Singer: " << head->singerName << " " << head->singerSurname << endl;
            cout << "Album: " << head->albumTitle << endl;
            cout << "Likes: " << head->likes << endl;
            cout << "---------------------" << endl;
        } else {
            cout << "No previous song available." << endl;
        }
    }

    // Μέθοδος για την αναπαραγωγή όλων των τραγουδιών σε τυχαία σειρά
    void playAllRandom() {
    cout << "Playing all songs in random order..." << endl;

    // Μέτρηση του αριθμού των τραγουδιών στην Playlist
    int count = 0;
    Song* current = head;
    while (current != nullptr) {
        ++count;
        current = current->next;
    }

    //Δημιουργία πίνακα για να ξέρουμε αν καθένα από τα τραγούδια παίχτηκαν ήδη
    bool* played = new bool[count]; // Αρχικά κανένα από τα τραγούδια δεν έχει παιχτεί

    // Παίξε κάθε τραγούδι σε τυχαία σειρά
    srand(time(nullptr)); // Εφαρμόζω το random number generator από τη βιβλιοθήκη
    for (int i = 0; i < count; ++i) {
        int index;
        do {
            index = rand() % count; // Δημιουργώ τυχαίο index
        } while (played[index]); // Συνεχίζω να δημιουργώ τυχαίο index μέχρι να βρω τραγούδι που δεν έχει παιχτεί
        played[index] = true; // Σημειώνω το τραγούδι ως "παιγμένο"
        
        // Παίζω το τραγούιδ με το τυχαίο index
        current = head;
        for (int j = 0; j < index && current != nullptr; ++j) {
            current = current->next;
        }
        if (current != nullptr) {
            cout << "Title: " << current->title << endl;
            cout << "Singer: " << current->singerName << " " << current->singerSurname << endl;
            cout << "Album: " << current->albumTitle << endl;
            cout << "Likes: " << current->likes << endl;
            cout << "---------------------" << endl;
        } else {
            cout << "Error: Song not found." << endl;
        }
    }

    // Ελευθερώνω την μνήμη που έχει δεσμευτεί για τον πίνακα
    delete[] played;
}

    // Μέθοδος για τη μετακίνηση ενός τραγουδιού σε μια άλλη θέση στη λίστα
    void moveSong(int currentPosition, int newPosition) {
    if (currentPosition == newPosition || currentPosition < 1 || newPosition < 1) {
        cout << "Invalid move. Please ensure positions are valid and different." << endl;
        return;
    }

    if (head == nullptr) {
        cout << "Playlist is empty. Cannot move song." << endl;
        return;
    }

    if (tail == nullptr) {
        cout << "Error: Tail pointer is null." << endl;
        return;
    }

    int count = 1;
    Song* current = head;
    Song* songToMove = nullptr;

    // Βρίσκω το τραγούδι προς μετακίνιση και το διαγράφω από τη λίστα
    while (current != nullptr && count <= currentPosition) {
        if (count == currentPosition) {
            songToMove = current;
            if (current->prev != nullptr) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }
            if (current->next != nullptr) {
                current->next->prev = current->prev;
            } else {
                tail = current->prev;
            }
            break;
        }
        current = current->next;
        count++;
    }

    if (songToMove == nullptr) {
        cout << "Invalid move. Current position out of range." << endl;
        return;
    }

    count = 1;
    current = head;

    // Βρίσκω τη θέση στη λίστα που θα μετακινήσω το τραγούδι
    while (current != nullptr && count <= newPosition) {
        if (count == newPosition) {
            // Εάν η θέση newPosition υπερβαίνει το μέγεθος της λίστας, το τραγούδι προστίθεται στο τέλος της
            if (count == newPosition && current == nullptr) {
                // Ενημέρωση του δείκτη next του προηγούμενου τελευταίου τραγουδιού
                if (tail != nullptr) {
                    tail->next = songToMove;
                }
                // Ενημέρωση του δείκτη prev του νέου τραγουδιού
                songToMove->prev = tail;
                // Το νέο τραγούδι γίνεται το νέο τελευταίο τραγούδι της λίστας
                tail = songToMove;
                cout << "Moved song from position " << currentPosition << " to position " << newPosition << " successfully." << endl;
                return;
            } else {
                // Εισαγωγή του τραγουδιού σε μια μεσαία θέση της λίστας
                if (current->prev != nullptr) {
                    current->prev->next = songToMove;
                } else {
                    head = songToMove;
                }
                //Ενημέρωση των δεικτών
                songToMove->prev = current->prev;
                songToMove->next = current;
                current->prev = songToMove;
                cout << "Moved song from position " << currentPosition << " to position " << newPosition << " successfully." << endl;
                return;
            }
        }
        current = current->next;
        count++;
    }

    // Εάν η θέση newPosition υπερβαίνει το μέγεθος της playlist, πρόσθεσε το τραγούδι στο τέλος της
    if (count == newPosition && current == nullptr) {
        // Ενημέρωση του δείκτη next του τελευταίου τραγουδιού
        if (tail != nullptr) {
            tail->next = songToMove;
        }
        // Ενημέρωση του δείκτη prev του νέου τραγουδιού
        songToMove->prev = tail;
        // Το νέο τραγούδι γίνεται το νέο τελευταίο τραγούδι της λίστας
        tail = songToMove;
        cout << "Moved song from position " << currentPosition << " to position " << newPosition << " successfully." << endl;
    } else {
        cout << "Invalid move. New position out of range." << endl;
    }
    }

    // Υλοποίηση της συνάρτησης ταξινόμησης με βάση τον τίτλο του τραγουδιού
    bool sortByTitle(const Song* a, const Song* b) {
    return a->title < b->title;
    }

    // Υλοποίηση της συνάρτησης ταξινόμησης με βάση το όνομα του τραγουδιστή
    bool sortBySingerFirstName(const Song* a, const Song* b) {
        return a->singerName < b->singerName;
    }

    // Υλοποίηση της συνάρτησης ταξινόμησης με βάση το επώνυμο του τραγουδιστή
    bool sortBySingerLastName(const Song* a, const Song* b) {
        return a->singerSurname < b->singerSurname;
    }

    // Υλοποίηση της συνάρτησης ταξινόμησης με βάση τον αριθμό των likes
    bool sortByLikesDescending(const Song* a, const Song* b) {
        return a->likes > b->likes;
    }

    // Μέθοδος για την ταξινόμηση της λίστας τραγουδιών
    void sortPlaylist() {
    int sortChoice;
    do {
        cout << "Sort Options:" << endl;
        cout << "1. Sort playlist by song title" << endl;
        cout << "2. Sort playlist by singers first name" << endl;
        cout << "3. Sort playlist by singers last name" << endl;
        cout << "4. Sort playlist by number of likes (decreasing)" << endl;
        cout << "5. Cancel / Save & Exit" << endl;
        cout << "Enter your choice: ";
        cin >> sortChoice;

        switch (sortChoice) {
            case 1: {
                // Κλήση της συνάρτησης sortPlaylistByTitle
                sortPlaylistByTitle();
                break;
            }
            case 2: {
                // Κλήση της συνάρτησης sortPlaylistBySingerFirstName
                sortPlaylistBySingerFirstName();
                break;
            }
            case 3: {
                // Κλήση της συνάρτησης sortPlaylistBySingerLastName
                sortPlaylistBySingerLastName();
                break;
            }
            case 4: {
                // Κλήση της συνάρτησης sortPlaylistByLikesDescending
                sortPlaylistByLikesDescending();
                break;
            }
            case 5: {
                cout << "Going back to the main menu...\n";
                return;
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        }

        printPlaylist();
    } while (sortChoice != 5);
    }

    // Υλοποίηση της συνάρτησης sortPlaylistByTitle
    void sortPlaylistByTitle() {
    // Έλεγχος αν η λίστα είναι άδεια
    if (head == nullptr) {
        cout << "Playlist is empty. Cannot sort.\n";
        return;
    }
    
    // Μεταβλητή για τον έλεγχο, αν υπήρξε ανταλλαγή σε κάθε πέρασμα
    bool swapped;
    // Δείκτες για την προσπέλαση της λίστας
    Song *ptr1, *lptr = nullptr;

    // Επανάληψη μέχρι να μην υπάρχουν περαιτέρω ανταλλαγές
    do {
        swapped = false;
        ptr1 = head;
        // Διάσχιση όλων των κόμβων της λίστας
        while (ptr1->next != lptr) {
            // Σύγκριση των τίτλων των τραγουδιών και ανταλλαγή αν χρειαστεί
            if (ptr1->title > ptr1->next->title) {
                swap(ptr1->title, ptr1->next->title);
                swap(ptr1->singerName, ptr1->next->singerName);
                swap(ptr1->singerSurname, ptr1->next->singerSurname);
                swap(ptr1->albumTitle, ptr1->next->albumTitle);
                swap(ptr1->likes, ptr1->next->likes);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped); // Επανάληψη μέχρι να μην υπάρχουν άλλες ανταλλαγές
}


// Υλοποίηση της συνάρτησης sortPlaylistBySingerFirstName
void sortPlaylistBySingerFirstName() {
    // Έλεγχος αν η λίστα είναι άδεια
    if (head == nullptr) {
        cout << "Playlist is empty. Cannot sort.\n";
        return;
    }
    
    // Μεταβλητή για τον έλεγχο αν υπήρξε ανταλλαγή σε κάθε πέρασμα
    bool swapped;
    // Δείκτες για την προσπέλαση της λίστας
    Song *ptr1, *lptr = nullptr;

    // Επανάληψη μέχρι να μην υπάρχουν περαιτέρω ανταλλαγές
    do {
        swapped = false;
        ptr1 = head;
        // Διάσχιση όλων των κόμβων της λίστας
        while (ptr1->next != lptr) {
            // Σύγκριση των ονομάτων των τραγουδιστών και ανταλλαγή αν χρειαστεί
            if (ptr1->singerName > ptr1->next->singerName) {
                swap(ptr1->title, ptr1->next->title);
                swap(ptr1->singerName, ptr1->next->singerName);
                swap(ptr1->singerSurname, ptr1->next->singerSurname);
                swap(ptr1->albumTitle, ptr1->next->albumTitle);
                swap(ptr1->likes, ptr1->next->likes);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped); // Επανάληψη μέχρι να μην υπάρχουν άλλες ανταλλαγές
}


// Υλοποίηση της συνάρτησης sortPlaylistBySingerLastName
void sortPlaylistBySingerLastName() {
    // Έλεγχος αν η λίστα είναι άδεια
    if (head == nullptr) {
        cout << "Playlist is empty. Cannot sort.\n";
        return;
    }
    
    // Μεταβλητή για τον έλεγχο αν υπήρξε ανταλλαγή σε κάθε πέρασμα
    bool swapped;
    // Δείκτες για την προσπέλαση της λίστας
    Song *ptr1, *lptr = nullptr;

    // Επανάληψη μέχρι να μην υπάρχουν περαιτέρω ανταλλαγές
    do {
        swapped = false;
        ptr1 = head;
        // Διάσχιση όλων των κόμβων της λίστας
        while (ptr1->next != lptr) {
            // Σύγκριση των επωνύμων των τραγουδιστών και ανταλλαγή αν χρειαστεί
            if (ptr1->singerSurname > ptr1->next->singerSurname) {
                swap(ptr1->title, ptr1->next->title);
                swap(ptr1->singerName, ptr1->next->singerName);
                swap(ptr1->singerSurname, ptr1->next->singerSurname);
                swap(ptr1->albumTitle, ptr1->next->albumTitle);
                swap(ptr1->likes, ptr1->next->likes);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped); // Επανάληψη μέχρι να μην υπάρχουν άλλες ανταλλαγές
}

// Υλοποίηση της συνάρτησης sortPlaylistByLikesDescending
void sortPlaylistByLikesDescending() {
    // Έλεγχος αν η λίστα είναι άδεια
    if (head == nullptr) {
        cout << "Playlist is empty. Cannot sort.\n";
        return;
    }
    
    // Μεταβλητή για τον έλεγχο αν υπήρξε ανταλλαγή σε κάθε πέρασμα
    bool swapped;
    // Δείκτες για την προσπέλαση της λίστας
    Song *ptr1, *lptr = nullptr;

    // Επανάληψη μέχρι να μην υπάρχουν περαιτέρω ανταλλαγές
    do {
        swapped = false;
        ptr1 = head;
        // Διάσχιση όλων των κόμβων της λίστας
        while (ptr1->next != lptr) {
            // Σύγκριση του αριθμού των likes και ανταλλαγή αν χρειαστεί
            if (ptr1->likes < ptr1->next->likes) {
                swap(ptr1->title, ptr1->next->title);
                swap(ptr1->singerName, ptr1->next->singerName);
                swap(ptr1->singerSurname, ptr1->next->singerSurname);
                swap(ptr1->albumTitle, ptr1->next->albumTitle);
                swap(ptr1->likes, ptr1->next->likes);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped); // Επανάληψη μέχρι να μην υπάρχουν άλλες ανταλλαγές
    }

};

int main() {
    // Δημιουργία αντικειμένου Playlist με το όνομα "My Playlist"
    Playlist myPlaylist("My Playlist");
    int choice;

    // Επανάληψη μέχρι ο χρήστης να επιλέξει την επιλογή "Exit"
    do {
        // Εμφάνιση του μενού
        cout << "Menu:\n";
        cout << "1. Insert new song into playlist\n";
        cout << "2. Play next song in playlist\n";
        cout << "3. Play previous song in playlist\n";
        cout << "4. Play all songs in playlist in random order\n";
        cout << "5. Move song to another position in playlist\n";
        cout << "6. Sort playlist\n";
        cout << "7. Print playlist to screen\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Εκτέλεση της επιλογής του χρήστη
        switch (choice) {
            case 1: {
                // Εισαγωγή νέου τραγουδιού στη λίστα
                string title, singerName, singerSurname, albumTitle;
                int likes;
                cout << "Enter title of song: ";
                cin.ignore(); // Αγνόηση του newline χαρακτήρα από το προηγούμενο cin
                getline(cin, title);
                cout << "Enter name of singer: ";
                getline(cin, singerName);
                cout << "Enter surname of singer: ";
                getline(cin, singerSurname);
                cout << "Enter title of album: ";
                getline(cin, albumTitle);
                cout << "Enter number of likes: ";
                cin >> likes;
                cin.ignore(); // Αγνόηση του newline χαρακτήρα από το προηγούμενο cin
                myPlaylist.insertSong(Song(title, singerName, singerSurname, albumTitle, likes));
                break;
            }
            case 2: {
                // Αναπαραγωγή του επόμενου τραγουδιού στη λίστα
                myPlaylist.nextSong();
                break;
            }
            case 3: {
                // Αναπαραγωγή του προηγούμενου τραγουδιού στη λίστα
                myPlaylist.prevSong();
                break;
            }
            case 4: {
                // Αναπαραγωγή όλων των τραγουδιών σε τυχαία σειρά
                myPlaylist.playAllRandom();
                break;
            }
            case 5: {
                // Μετακίνηση ενός τραγουδιού σε άλλη θέση στη λίστα
                int currentPosition, newPosition;
                cout << "Enter current position of the song: ";
                cin >> currentPosition;
                cout << "Enter new position for the song: ";
                cin >> newPosition;
                myPlaylist.moveSong(currentPosition, newPosition);
                break;
            }
            case 6: {
                // Ταξινόμηση της λίστας
                myPlaylist.sortPlaylist();
                break;
            }
            case 7: {
                // Εκτύπωση της λίστας
                myPlaylist.printPlaylist();
                break;
            }
            case 8: {
                // Έξοδος από το πρόγραμμα
                cout << "Exiting program...\n";
                break;
            }
            default: {
                // Μήνυμα λάθους για μη έγκυρη επιλογή
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    } while (choice != 8); // Επανάληψη μέχρι ο χρήστης να επιλέξει την επιλογή "Exit"

    return 0;
}