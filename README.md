# battleship
 This project is a simulation of a battleship game
Λογική προγράμματος

Η λογική του προγράμματος υλοποιείται στην κλάση Naumaxia. Ένα στιγμιότυπο της
κλάσης αυτής αντιπροσωπεύει ένα παιχνίδι (μια παρτίδα) ναυμαχίας. Στην main λοιπόν
δημιουργείται ένα αντικείμενο Naumaxia και από εκεί και έπειτα του παραχωρείται ο
έλεγχος του προγράμματος με κλήση της μεθόδου play. Πριν από αυτό ανατίθενται οι
απαραίτητες τιμές σε ορισμένες παραμέτρους του παιχνιδιού, όπως για παράδειγμα το
όριο καιρού για πρόκληση ζημιάς. Αυτές οι παράμετροι έχουν προκαθορισμένες τιμές, αλλά
με αυτόν τον τρόπο έχουμε την δυνατότητα, προγραμματιστικά, να καθορίζουμε την
δυσκολία του παιχνιδιού. Έτσι είναι δυνατόν να υλοποιηθούν διαφορετικά επίπεδα
δυσκολίας.

Βρόχος παιχνιδιού

Η μέθοδος play υλοποιεί έναν πολύ απλό βρόχο παιχνιδιού. Σε επανάληψη εφαρμόζει τους
κανόνες του παιχνιδιού στην αρχή του βήματος, στην συνέχεια καλεί για κάθε πλοίο τις
μεθόδους μετακίνησης και λειτουργίας και τέλος εφαρμόζει ορισμένους κανόνες στο τέλος
του βήματος. Όλο αυτό βρίσκεται στο σώμα ενός while που ελέγχει αν ικανοποιείται η
συνθήκη τερματισμού του παιχνιδιού. Όσο δεν ικανοποιείται, συνεχίζει ο βρόχος.
Κλάση πλοίο / Κληρονομικότητα
Για να μπορεί να καλείται η μετακίνηση και η λειτουργία σε κάθε πλοίο χωρίς να
γνωρίζουμε καν τι τύπου είναι, υπάρχει μια κλάση Ship που κάθε τύπος πλοίου κληρονομεί.
Έτσι, σε ένα std::vector<Ship*> διατηρούμε έναν πίνακα με όλα τα ενεργά πλοία του
παιχνιδιού. Το συγκεκριμένο vector είναι μέλος της κλάσης Naumaxia.

Χάρτης παιχνιδιού

Εκτός από το vector με base pointers στα πλοία, υπάρχει σαν μέλος της κλάσης Naumaxia
ένας δισδιάστος πίνακας με όνομα map, υλοποιημένος σαν vector από vectors που
αντιπροσωπεύει τον χάρτη του παιχνιδιού. Κάθε θέση του map είναι ένα αντικείμενο τύπου
Cell. Η κλάση Cell περιέχει την πληροφορία που αφορά κάθε μεμονωμένο σημείο του
χάρτη. Πέρα από τα προφανή, {καιρός, θησαυρός, λιμάνι} περιέχει έναν pointer Ship* που
δείχνει στο πλοίο αυτής της θέσης, αν υπάρχει, αλλιώς είναι NULL. Έτσι, έχουμε έναν
εναλλακτικό τρόπο να έχουμε πρόσβαση στα καράβια, κάνοντας πολύ πιο υπολογιστικά
αποδοτικό το να βρούμε τα γειτονικά πλοία ενός πλοίου δεδομένης της θέσης του στον
χάρτη. Σε αντίθετη περίπτωση, αν δηλαδή τα πλοία τα διατηρούσαμε αποκλειστικά σε δομή
πίνακα, για να βρούμε αν μια θέση έχει πλοίο και ποιο είναι αυτό, θα έπρεπε να
διατρέξουμε (αναζήτηση) ολόκληρο τον πίνακα.

Πρόσβαση πλοίων σε περιβάλλον

Στην μέθοδο λειτουργίας, κάποια πλοία πρέπει να πάρουν αποφάσεις που δεν εξαρτώνται
αποκλειστικά από τα ίδια, αλλά και από το περιβάλλον τους (καιρός, γείτονες, κτλ.). Για να
γίνει εφικτή η υλοποίηση τέτοιων λειτουργιών, κάθε αντικείμενο τύπου Ship έχει έναν
δείκτη τύπου Naumaxia και η κλάση Naumaxia με την σειρά της μια σειρά από public
μεθόδους μέσω των οποίων τα πλοία μπορούν να “ρωτούν” τις απαραίτητες πληροφορίες
για το περιβάλλον τους π.χ. std::vector<Coords> getFreeNeigbourCells(const int row, const int col);.

Διεπαφή χρήστη

Η διεπαφή γίνεται μέσω της γραμμής εντολών. Σε κάθε βήμα η προσομοίωση εκτελεί ένα
σύντομο Sleep ώστε να μπορεί να προλάβει ο χρήστης να διακόψει για να ρωτήσει
πληροφορίες. Επίσης ελέγχεται τυχόν είσοδος από το πληκτρολόγιο χωρίς να περιμένει
υποχρεωτικά για enter (non-blocking). Με το πλήκτρο διαστήματος, διακόπτεται η ροή της
προσομοίωσης και μέσω ενός μενού ο χρήστης μπορεί να ζητήσει πληροφορίες.