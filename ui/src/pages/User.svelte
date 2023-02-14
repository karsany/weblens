<script>
    let delProgress = false;
    function login() {
        console.log(settings);

        fetch("/api/user/save", {
            method: "POST",
            headers: {
                "Content-Type": "application/json",
            },
            body: JSON.stringify(settings),
        })
            .then((response) => {
                console.log(response);
                return response.json();
            })
            .then((data) => {
                alert("Felhasználói adatok mentve");
            });
    }

    let settings = { pictureUrl: "", additionalFields: "" };
</script>

<div class="card">
    <header>User settings</header>

    <table>
        <tr>
            <th>
                <label for="picture_url">Picture send URL</label>
            </th>
            <td>
                <input
                    type="text"
                    name="picture_url"
                    bind:value={settings.pictureUrl}
                />
            </td>
        </tr>
        <tr>
            <th>
                <label for="additional_fields">Additional fields JSON</label>
            </th>
            <td>
                <textarea
                    name="additional_fields"
                    bind:value={settings.additionalFields}
                />
            </td>
        </tr>
    </table>

    <footer class="is-right">
        <button on:click={login}> Save </button>
    </footer>
</div>
