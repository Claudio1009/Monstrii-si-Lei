import pandas as pd
from googletrans import Translator

# Citeste fisierul CSV in limba romana
df = pd.read_csv('diete.csv', encoding='utf-8')

# Initializeaza un obiect Translator
translator = Translator()

# Creeaza o lista cu toate textele din fisierul CSV
text_to_translate = df['text_column'].tolist()

# Traduce fiecare text in lista si salveaza rezultatul in alta lista
translated_text = []
for text in text_to_translate:
    translated_text.append(translator.translate(text, dest='en').text)

# Adauga coloana cu textul tradus in dataframe-ul original
df['translated_text'] = translated_text

# Scrie dataframe-ul intr-un nou fisier CSV in limba engleza
df.to_csv('fisier_englez.csv', encoding='utf-8', index=False)
