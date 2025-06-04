import subprocess

from fastapi import FastAPI, Query

app = FastAPI(title="Terminal")

regex_spanish = r"^[A-Za-zÁÉÍÓÚÜÑáéíóúüñ\s]*$"


@app.post("/scores", tags=["Score"])
async def insert(
    score: int = Query(..., ge=1, lt=6),  # greater than 1 and less than 6
    message: str = Query("", regex=regex_spanish, max_length=255),
    user: str = Query("", regex=regex_spanish, max_length=255),
):
    # ./score insert score --message "message" --user "user"
    result = subprocess.run(
        ["./score", "insert", str(score), "--message", message, "--user", user]
    )
    return {"result": result.returncode}


@app.get("/scores", tags=["Score"])
async def get_all():
    # ./score get
    result = subprocess.run(["./score", "get"], capture_output=True, text=True)
    scores = result.stdout.splitlines()
    return {"scores": scores}
