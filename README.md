## Build instructions

1. Install dependencies:

```bash
python3 -m venv .venv
. .venv/bin/activate
pip install -r requirements.txt
```

2. Copy NTSC 1.0 US ROM to `oot/baserom_oot_ne0.z64`.

3. Build:

```bash
make setup
make disasm
make
```
