# 🔐 Armários Inteligentes com ESP32 + RFID

Este projeto consiste na implementação de um sistema de armários inteligentes com controle de acesso via cartões e tags RFID. Cada armário é representado por uma placa ESP32 conectada a um leitor MFRC522, capaz de identificar usuários por meio do UID dos cartões. As informações de uso são sincronizadas em tempo real com o Firebase Realtime Database.

Além disso, uma interface web simples foi desenvolvida e hospedada no Firebase Hosting, permitindo a visualização dinâmica do estado dos armários (abertos ou fechados), conforme a interação física com os leitores RFID.

## 🚀 Funcionalidades

- Leitura de cartões RFID para realizar reserva ou liberação de armários.
- Sincronização em tempo real com o Firebase Realtime Database.
- Interface web responsiva para exibição do status dos armários.
- Identificação e controle por UID individual de cartões RFID.

## 🛠 Tecnologias Utilizadas

- ESP32
- Leitor RFID MFRC522
- Firebase Realtime Database
- Firebase Hosting (HTML/CSS/JS)
- Arduino IDE

## 🧾 Estrutura do Firebase

O banco de dados segue a estrutura abaixo no Firebase Realtime Database:

```
/lockers
  ├── locker_01
  │   ├── id: "001"
  │   ├── status: "closed"
  │   ├── uid: "AAAAAAA"
  │   └── lastAccess: "000000"
  └── locker_02
      ├── id: "002"
      ├── status: "open"
      ├── uid: "null"
      └── lastAccess: "000000"
```

Cada armário possui um identificador único (`id`), um status atual (`open` ou `closed`), o UID associado (`uid`) e um timestamp da última interação (`lastAccess`).

## 📁 Organização do Projeto

- `locker_esp/` – Contém o código embarcado da ESP32 responsável por controlar um armário.
- `web/` – Contém os arquivos da interface web, hospedada no Firebase Hosting.

⚠️ Este repositório contém apenas o código configurado para o `locker_01`. Para adicionar novos armários, como `locker_02`, `locker_03`, etc., basta duplicar o código da ESP32 e alterar o valor da constante `LOCKER_ID` no arquivo `secrets.h`.

## 🔒 Credenciais

As credenciais sensíveis, como dados de Wi-Fi e Firebase, foram separadas no arquivo `secrets.h`, que **não é versionado** no repositório. Para executar o projeto, crie localmente o arquivo `secrets.h` com o seguinte conteúdo:

```cpp
#define WIFI_SSID "SUA_REDE_WIFI"
#define WIFI_PASSWORD "SUA_SENHA"
#define API_KEY "SUA_API_KEY"
#define DATABASE_URL "https://seuprojeto.firebaseio.com/"
#define USER_EMAIL "seu@email.com"
#define USER_PASSWORD "suaSenha"
#define LOCKER_ID "locker_01"
```

> ⚠️ Lembre-se de adicionar `secrets.h` ao `.gitignore` para evitar o versionamento acidental das credenciais.

Na aplicação web, o objeto `firebaseConfig` foi movido para um arquivo separado chamado `firebase-config.js`, que também está listado no `.gitignore`. Esse arquivo deve ser criado com o seguinte conteúdo:

```js
// firebase-config.js
const firebaseConfig = {
    apiKey: "SUA_API_KEY",
    authDomain: "SEU_AUTH_DOMAIN",
    databaseURL: "SUA_DATABASE_URL",
    projectId: "SEU_PROJECT_ID",
    storageBucket: "SEU_BUCKET",
    messagingSenderId: "SEU_SENDER_ID",
    appId: "SEU_APP_ID"
};
```

No HTML da aplicação web, o script deve ser incluído antes do `script.js`:

```html
<script src="firebase-config.js"></script>
<script src="script.js"></script>
```

## 📄 .gitignore (exemplo)

```
secrets.h
web/firebase-config.js
web/.firebase/
```

## 👨‍💻 Autores

Projeto desenvolvido por **João Pedro Ramalho de Sousa**, **Matheus Bertoldo** e **Renan Ribeiro Pereira**, como parte da disciplina de Internet das Coisas na Universidade Federal de Lavras (UFLA).
