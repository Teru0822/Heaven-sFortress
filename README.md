# Heaven's Fortress

**Heaven's Fortress** は、様々なミニゲーム（チェス、戦車戦、レース、シューティング）を楽しめるオンラインマルチプレイヤーゲームです。

## 必要要件

- **OS**: Windows 10/11, macOS, Linux
- **ライブラリ**: SDL2, SDL2_mixer, GLEW, OpenGL (freeglut)

## インストール方法

### Windows
1. Releasesページからインストーラー(`.exe`)をダウンロードします。
2. インストーラーを実行し、画面の指示に従ってインストールしてください。

### macOS / Linux
Releaseページから `.dmg` (macOS) または `.deb`/`.tar.gz` (Linux) をダウンロードしてインストールしてください。

## 実行方法

このゲームはクライアント・サーバー方式で動作します。遊ぶにはサーバーを立ち上げ、そこにプレイヤー（クライアント）が接続する必要があります。

### 1. サーバーの起動
コマンドライン（またはターミナル）からサーバープログラムを実行します。

```bash
# Windows
HeavensFortressServer.exe [クライアント数] [ポート番号]

# 例: 2人で遊ぶ場合、ポート10000を使用
HeavensFortressServer.exe 2 10000
```
※ ポート番号を省略した場合、デフォルトポートが使用されます。

### 2. クライアントの接続
各プレイヤーはクライアントプログラムを実行し、サーバーに接続します。

```bash
# Windows
HeavensFortressClient.exe [サーバーIP] [ポート番号]

# 例1: 自分のPCでサーバーも動かしている場合 (ローカル接続)
HeavensFortressClient.exe 127.0.0.1 50100

# 例2: 同じネットワーク内の別のPC (IP: 192.168.1.10) のサーバーに接続する場合
HeavensFortressClient.exe 192.168.1.10 50100
```

### Linuxでの実行
実行時に `libSDL2_mixer` などのライブラリが見つからないエラーが出る場合は、必要なランタイムライブラリをインストールしてください。

#### 依存ライブラリのインストール (Ubuntu/Debian系)
```bash
sudo apt-get update
sudo apt-get install libsdl2-2.0-0 libsdl2-mixer-2.0-0 libglew2.2 libfreeglut3 libgomp1
```

#### 実行コマンド
実行権限を付与してから実行します。
```bash
chmod +x HeavensFortressServer HeavensFortressClient

# サーバー
./HeavensFortressServer 2 50100

# クライアント
./HeavensFortressClient 127.0.0.1 50100
```

起動後、プレイヤー名を入力してゲームに参加します。

## ゲームモード (Scenes)

ゲーム内には「広場」と呼ばれるロビーがあり、そこから各ゲームモードへ移動できます。

1.  **Portal (広場)**: ロビーエリア。他のプレイヤーとチャットしたり、各ゲームへのポータルに入ることができます。
2.  **Chess (チェス)**: 戦略ボードゲーム。2人のプレイヤーで対戦します。
3.  **Tank (戦車戦)**: 戦車に乗って砲撃戦を行います。
4.  **Race (レース)**: スポーツカーでコースを競走します。
5.  **Shooting (シューティング)**: 銃を使ったFPS/TPS視点の戦闘です。

## 操作方法

基本操作はキーボードとマウスを使用します。

### 共通操作
- **移動**: W, A, S, D
- **ジャンプ**: Space
- **視点移動**: マウス移動
- **メニュー/終了**: Esc

### 各モード特有の操作
- **戦車 (Tank)**:
  - **発射**: 左クリック
  - **砲塔旋回**: マウス移動
- **レース (Race)**:
  - **加速/減速**: W / S
  - **ハンドル**: A / D
  - **車種変更**: 数字キー '1', '2' (待機中のみ)
- **シューティング (Shooting)**:
  - **発砲**: 左クリック
  - **エイム (照準)**: 右クリック (ホールドまたはトグル)
- **チェス (Chess)**:
  - **駒の選択/配置**: マウス操作
  - **視点変更**: マウスドラッグ

## ビルド方法 (開発者向け)

ソースコードからビルドする場合は `CMake` を使用します。

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```
