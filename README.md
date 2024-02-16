# World_of_Tanks
### Ioan Teodorescu - 333CB

Acesta este un joc simplu, dar captivant, în care controlezi un tanc pe un plan orizontal plin de tancuri inamice și clădiri. Obiectivul jocului este să distrugi cât mai multe tancuri inamice într-un interval de timp limitat (2 minute). Primești puncte pentru fiecare tanc inamic distrus. Jocul este implementat in limbajul C++, cu ajutorul interfetei OpenGL pentru randarea obiectelor 2D si 3D.

## Mecanică de Joc

- **Controale**: Folosește tastele săgeată sau WASD pentru a mișca tancul și pentru a roti turela acestuia.
- **Obiectiv**: Distrugerea cât mai multor tancuri inamice înainte ca timpul să se scurgă.
- **Punctaj**: Primești puncte pentru fiecare tanc inamic distrus.
- **Proiectil**: Trage proiectile din tunul tancului pentru a distruge tancuri inamice și clădiri.
- **Sănătatea Tancului**: Tancurile inamice pot rezista la un minim de 4 lovituri înainte de a fi distruse.
- **Vizualizare Avarii**: Tancurile inamice devin tot mai deteriorate, reprezentate vizual prin deformări și întunecare, pe măsură ce primesc lovituri.
- **Sfârșitul Jocului**: Jocul se încheie atunci când este atinsă limita de timp sau când tancul jucătorului este distrus.

## Caracteristici Avansate

- **Rotația Turelei**: Rotește turela pentru a ținti inamicii (cerință avansată).
- **Mișcarea Tancurilor Inamice**: Tancurile inamice se mișcă fie pe trasee predefinite (cerință de bază), fie aleator (cerință avansată).
- **Atacul Tancurilor Inamice**: Tancurile inamice își rotesc turelele către jucător pentru a trage proiectile.

## Sfârșitul Jocului

- **Limita de Timp Atinsă**: Dacă se atinge limita de timp, jocul se încheie, afișând scorul final.
- **Tancul Jucătorului Distrus**: Dacă tancul jucătorului este distrus, se afișează un mesaj corespunzător.

![atac](/readmeimgs/atac.gif "atac")